/*
 * parser.h
 *
 *  Created on: 26 Mar 2015
 *      Author: stijn & evert
 */

#include <iostream>
#include <string>

#include "../../../lib/tinyxml/tinyxml.h"

#ifndef _Parser
#define _Parser


class ParseError: std::exception {
public:
	ParseError(std::string info, std::string filename):
			_info(info), _filename(filename) {}
	
	const char* what()throw() {
		std::string s;
		s += "Error while parsing the XML file \'";
		s += _filename + "\': " + _info;
		return s.c_str();
	}
	
private:
	std::string _info;
	std::string _filename;
};

class Parser {
public:
	Parser();
	
	Parser(std::ostream* stream, std::string filename="UNKNOWN");

	void set_out(std::ostream* stream);

protected:
	std::ostream* _out;
	std::string _filename;  // for debugging purposes

	// Error handling
	void format_message(std::string& msg, TiXmlBase* el);
	void log(std::string msg, TiXmlBase* el=nullptr);  // logs to out, if it is set.
	void fatal(std::string msg, TiXmlBase* el=nullptr);  // throws ParseError

	std::string readElement(TiXmlElement* elem, const char* tag);

	std::string readElement(TiXmlElement* elem);

	std::string readAttribute(TiXmlElement* elem, const char* tag);

	bool reqElement(TiXmlElement* elem, const char* tag);
};



#endif /* _Parser*/
