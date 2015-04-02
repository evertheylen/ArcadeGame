/*
 * parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */
#include <iostream>
#include "parser.h"

NullableStream::NullableStream() {
	_out = nullptr;
}

void NullableStream::set_out(std::ostream* out) {
	_out = out;
}

Parser::Parser() {
	out.set_out(nullptr);
}

std::string Parser::readElement(TiXmlElement* elem, const char* tag) {
	if (elem == NULL) {
		//out << "Error: Error: Tag not defined.";
		throw(ParseError());
	}
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (elem == NULL) throw(ParseError());
	TiXmlNode* node = e->FirstChild();
	if (node == NULL) throw(ParseError());
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
	if (elem == nullptr || elem->Attribute(tag) == nullptr) {
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

/*void Parser::print(std::string msg) {
	if (out.get_out() != nullptr) {
		out << "Something went wrong while parsing: " << msg << "\n";
	}
}

void Parser::set_out(std::ostream* new_out) {
	out = new_out;
}*/

