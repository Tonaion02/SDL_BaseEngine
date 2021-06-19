#pragma once

#include "PrecompiledHeaders.h"

#include "Format.h"





struct XMLvariab
{
public:
	XMLvariab() {}
	XMLvariab(const std::string& line);

	std::string getValue(const std::string& key);

public:
	std::string name;
	std::unordered_map<std::string, std::string> values;

	//Da aggiungere in futuro(possibilità di ottenere a partire da un unordered_map e un nome una linea da inserire in un testo)
	//std::string getLineFromValues(const std::string& name);
};