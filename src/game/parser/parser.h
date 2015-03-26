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


class NullableStream {
public:
	NullableStream();
	void set_out(std::ostream* out);

private:
	std::ostream* _out;
};

class ParseError: std::exception {
	const char* what()throw() {
		return "Error while parsing the xml file.";
	}
};

class Parser {
public:
	Parser();

	void set_out(std::ostream* out);

protected:
	NullableStream out;

	void print(std::string msg);

	std::string readElement(TiXmlElement* elem, const char* tag);

	std::string readElement(TiXmlElement* elem);

	std::string readAttribute(TiXmlElement* elem, const char* tag);

	bool reqElement(TiXmlElement* elem, const char* tag);
};



#endif /* _Parser*/
