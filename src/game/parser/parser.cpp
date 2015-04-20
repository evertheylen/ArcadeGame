/*
 * parser.cpp
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */
#include <iostream>
#include <string>
#include "parser.h"

Parser::Parser() {}

Parser::Parser(std::ostream* stream, std::string filename):
		_filename(filename), _out(stream) {}

std::string Parser::readElement(TiXmlElement* elem, const char* tag) {
	if (elem == nullptr) {
		fatal(std::string("Element was null"), elem);
	}
	TiXmlElement* e = elem->FirstChildElement(tag);
	if (elem == nullptr) fatal(std::string("Child element was null, with tag ") + tag, elem);
	TiXmlNode* node = e->FirstChild();
	if (node == nullptr) fatal("Node was null", elem);
	TiXmlText* text = node->ToText();
	if (text == nullptr) fatal("Text was null", elem);
	return text->Value();
}

std::string Parser::readElement(TiXmlElement* elem) {
	if (elem == nullptr) {
		fatal("Element not defined", elem);
	}
	TiXmlNode* node = elem->FirstChild();
	if (node == nullptr) fatal("Node was null", elem);
	TiXmlText* text = node->ToText();
	if (text == nullptr) fatal("Text was null", elem);
	return text->Value();
}

std::string Parser::readAttribute(TiXmlElement* elem, const char* tag) {
	if (elem == nullptr || elem->Attribute(tag) == nullptr) {
		fatal(std::string("Element was null or tag was not found. tag=") + tag, elem);
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


void Parser::set_out(std::ostream* new_out) {
	_out = new_out;
}

void Parser::format_message(std::string& msg, TiXmlBase* el) {
	msg += std::string(" [") + _filename;
	if (el != nullptr) {
		msg += std::string(":") + std::to_string(el->Row()) + ":" + std::to_string(el->Column());
	}
	msg += "]";
}

void Parser::fatal(std::string msg, TiXmlBase* el) {
	format_message(msg, el);
	throw ParseError(msg, _filename);
}

void Parser::log(std::string msg, TiXmlBase* el) {
	if (_out != nullptr) {
		format_message(msg, el);
		*_out << msg << "\n";
	}
}
