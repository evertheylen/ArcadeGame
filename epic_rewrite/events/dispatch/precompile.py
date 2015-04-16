#!/usr/bin/python3

import sys
import toml

hbase = """
class {name}: public {data[inherits]}<{data[returns]}, {arg_types}> {{
public:
    int getRule({parsed_args});
    
    {data[returns]} doRule(int rulenum, {parsed_args});
}};


"""

cppbase = """
// {name}

int {name}::getRule({parsed_args}) {{
{getrule_content}
    return -1;
}}
    
{data[returns]} {name}::doRule(int rulenum, {parsed_args}) {{
    switch(rulenum) {{
{dorule_content}
        default:
            return {dorule_defaultcall};
    }}
}}



"""

cpp_dorule_base = """
        case {i}:
            return {call};
"""



class Argument:
    def __init__(self, typename, name):
        self.typename = typename
        self.name = name
    
    def define(self):
        return self.typename + " " + self.name

class Rule:
    def __init__(self, types, priority):
        self.types = types
        self.priority = priority
        
    def call(self, funcname, varnames):
        args = []
        for i, t in enumerate(self.types):
            args.append("dynamic_cast<{}>({})".format(t, varnames[i]))
        return funcname + "(" + ", ".join(args) + ")"

    def get(self, args):
        tab = "    "
        s = tab+"// Rule {}\n".format(self.priority)
        varnames = []
        for i, t in enumerate(self.types):
            varname = "__r"+str(self.priority)+"_"+safetext(t)+str(i)
            s += tab+"{0} {1} = dynamic_cast<{0}>({2});\n".format(t, varname, args[i])
            varnames.append(varname)
        
        s += tab+"if ("+" && ".join(["{} != nullptr".format(varname) for varname in varnames]) +") {\n"
        s += tab+"    return {};\n".format(self.priority)
        s += tab+"}\n\n"
        return s
        

def safetext(s):
    for c in "*& \"\'!<>+-/\\=":
        s = s.replace(c, "")
    return s


def write_dispatcher(data, name, hfile, cppfile):
    #inherits = "SymmetricDoubleDispatch<void, Entity*, Entity*>"
    #funcname = "onCollision"
    #returns = "void"
	#args = ["Entity*", "Entity*"]
    #rules = [
        #["Player*", "Bomb*"],  # Highest priority
        #["Entity*", "Entity*"], # Default (lowest priority)
    #]
    
    # to define: parsed_args, arg_types, arg_names, dorule_content, dorule_defaultcall, getrule_content
    args = []
    for i, t in enumerate(data["args"]):
        args.append(Argument(t, "__"+safetext(t)+str(i)))
    
    rules = []
    for i, r in enumerate(data["rules"][:-1]):
        rules.append(Rule(r, i))
    defaultrule = Rule(data["rules"][-1], -1)
    
    parsed_args = ", ".join([a.define() for a in args])
    arg_types = ", ".join([a.typename for a in args])
    
    hfile.write(hbase.format(**locals()))
    
    
    arg_list = [a.name for a in args]
    arg_names = ", ".join(arg_list)
    dorule_content = "".join(
        [cpp_dorule_base.format(i=r.priority, call=r.call(data["funcname"], arg_list)) for r in rules])
    dorule_defaultcall = defaultrule.call(data["funcname"], arg_list)
    
    getrule_content = "".join([r.get(arg_list) for r in rules])
    
    cppfile.write(cppbase.format(**locals()))
                                
    
    
    
        

def main():
    filename = ""
    
    try:
        filename = sys.argv[1]
    except:
        print("Something went wrong while reading the file.")
        return
    
    with open(filename) as datafile:
        data = toml.load(datafile)
        name = filename[:filename.rfind(".")]
        hfile = open(name+".h", "w")
        hfile.write("#ifndef ___{0}\n#define ___{0}\n\n".format(name[name.rfind('/')+1:]))
        
        cppfile = open(name+".cpp", "w")
        cppfile.write("#include \"%s\"\n\n"%(name+".h"))
        
        if "header" in data:
            hfile.write(data["header"])
            cppfile.write(data["header"])
            data.pop("header")
        
        if "cppheader" in data:
            cppfile.write(data["cppheader"])
            data.pop("cppheader")
        
        for key in data:
            write_dispatcher(data[key], key, hfile, cppfile)
            print("Created dispatcher",key)
        
        hfile.write("\n#endif\n")
        hfile.close()
        cppfile.close()
    
    
if __name__=="__main__":
    main()
