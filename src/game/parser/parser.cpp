/*
 * parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include "parser.h"
#include <iostream>

std::string Parser::readElement(TiXmlElement* elem, const char* tag) {
	if (elem == nullptr) {
		//out << "Error: Error: Tag not defined.";
		throw(ParseError());
	}
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (elem == nullptr) throw(ParseError());
	TiXmlNode* node = e->FirstChild();
	if (node == nullptr) throw(ParseError());
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Parser::readElement(TiXmlElement* elem) {
	if (elem == nullptr) {
		//out << "Error: Error: Tag not defined.";
		throw(ParseError());
	}
	TiXmlNode* node = elem->FirstChild();
	if (node == nullptr) throw(ParseError());
	TiXmlText* text = node->ToText();
	return text->Value();
}

std::string Parser::readAttribute(TiXmlElement* elem, const char* tag) {
	if (elem == nullptr) {
		throw(ParseError());
	}
	return std::string(elem->Attribute(tag));
}

bool Parser::reqElement(TiXmlElement* elem, const char* tag) {
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (e == nullptr) {
		return false;
	}
	return true;
}

Parser::Parser(): _out(nullptr) {}

void Parser::print(std::string msg) {
	if (_out != nullptr) {
		_out << "Something went wrong while parsing: " << msg << "\n";
	}
}

void Parser::set_out(std::ostream* out) {
	_out = out;
}

