#!/usr/bin/python3

import xml.etree.ElementTree as ET
import sys

class Entity:
    def __init__(self, el):
        self.x = el.attrib["x"]
        self.y = el.attrib["y"]
        if "beweegbaar" in el.attrib:
            self.beweegbaar = el.attrib["beweegbaar"]
        else:
            self.beweegbaar = None
        type_el = el.find("TYPE")
        if type_el == None:
            self.typ = el.tag
        else:
            self.typ = type_el.text
        self.subs = []
        for subel in el:
            if subel.tag != "TYPE":
                self.subs.append(subel)
    
    def new_format(self):
        root = ET.Element(self.typ.upper())
        root.attrib = {'x': self.x, 'y': self.y}
        if self.beweegbaar != None:
            root.attrib['beweegbaar'] = self.beweegbaar
        for subel in self.subs:
            root.append(subel)
        root.tail = "\n"
        return root

class Board:
    # <NAAM>Level 1</NAAM>
    # <LENGTE>10</LENGTE>
    # <BREEDTE>10</BREEDTE>
    #  ...
    def __init__(self, tree):
        root = tree.getroot()
        self.naam = root.find("NAAM")
        self.lengte = root.find("LENGTE")
        self.breedte = root.find("BREEDTE")
        self.stuff = []
        for el in root:
            if el.tag not in ["NAAM", "LENGTE", "BREEDTE"]:
                self.stuff.append(Entity(el))
    
    def newtree(self):
        root = ET.Element('VELD')
        root.append(self.naam)
        root.append(self.lengte)
        root.append(self.breedte)
        for el in self.stuff:
            root.append(el.new_format())
        tree = ET.ElementTree(root)
        return tree
        

def main():
    dirname = sys.argv[1]
    tree = ET.parse(dirname+'/Speelveld.xml')
    b = Board(tree)
    b.newtree().write(dirname+'/Speelveld.xml')
    
    
if __name__=='__main__':
    main()
