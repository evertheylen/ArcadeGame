#!/usr/bin/python3

import xml.etree.ElementTree as ET
import sys

def element_as_prop(name, prop):
    el = ET.Element(name)
    el.text = str(prop)
    return el

def indent(elem, level=0):
    i = "\n" + level*"  "
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "  "
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
        for elem in elem:
            indent(elem, level+1)
        if not elem.tail or not elem.tail.strip():
            elem.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

class Entity:
    desc = "Entity"
    bew = "false"
    
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def attr(self):
        attrs = {'x': str(self.x), 'y': str(self.y), 'beweegbaar': self.bew}
        attrs.update(self.extra_attr())
        return attrs
    
    def extra_attr(self):
        return {}
    
    def to_xml(self):
        el = ET.Element(self.desc)
        el.attrib = self.attr()
        el.tail = '\n'
        return el
    
class Ton(Entity):
    desc = "TON"
    bew = "true"

class Doel(Entity):
    desc = "DOEL"
    
class Muur(Entity):
    desc = "MUUR"

class Speler(Entity):
    desc = "SPELER"
    bew = "true"

class Monster(Entity):
    desc = "MONSTER"

class Water(Entity):
    desc = "WATER"

class Valstrik(Entity):
    desc = "VALSTRIK"

class Knop(Entity):
    desc = "KNOP"

class Poort(Entity):
    desc = "POORT"

class Board:
    def __init__(self, width, height, name):
        self.width = width
        self.height = height
        self.name = name
        self.entities = []
    
    def to_xml(self):
        el = ET.Element("VELD")
        el.append(element_as_prop("BREEDTE", self.width))
        el.append(element_as_prop("LENGTE", self.height))
        el.append(element_as_prop("NAAM", self.name))
        el.extend([e.to_xml() for e in self.entities])
        return el
        
        

entity_map = {
    'o': Ton,
    'X': Doel,
    '#': Muur,
    'Y': Speler,
    '@': Monster,
    '~': Water,
    '/': Valstrik,  # not real, I know
    '.': Knop,
    '=': Poort,
}

def main():
    fname = sys.argv[1]
    f = open(fname)
    lines = f.readlines()
    
    b = Board(len(lines[0])-1, len(lines), "Autogenerated")
    
    for fake_y, line in enumerate(lines):
        y = b.height-fake_y-1
        for x, char in enumerate(line):
            if char in entity_map:
                b.entities.append(entity_map[char](x,y))
    
    el = b.to_xml()
    indent(el)
    tree = ET.ElementTree(el)
    tree.write(fname+".xml")
    
    
        

if __name__=='__main__':
    main()
    