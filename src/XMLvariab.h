#pragma once

#include "PrecompiledHeaders.h"

#include "Format.h"





struct XMLvariab
{
	XMLvariab() {}
	XMLvariab(const std::string& line);

	std::unordered_map<std::string, std::string> values;

	std::string getValue(const std::string& key);

	//Da aggiungere in futuro(possibilità di ottenere a partire da un unordered_map e un nome una linea da inserire in un testo)
	//std::string getLineFromValues(const std::string& name);
};