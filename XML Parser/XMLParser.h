#pragma once

#include <string>

class XMLParser {
public:
	XMLParser();
	~XMLParser();

	void Create(std::string file);
	void InsertValues();

};