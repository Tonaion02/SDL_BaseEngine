#pragma once

#include "XMLvariab.h"





struct XMLobject
{
	XMLobject() {}
	XMLobject(const std::string& filePath);

	std::vector<XMLvariab> xmlVariabs;
	std::string name;
};





//Forse inutile
struct CacheXML
{
	CacheXML() {}

	std::unordered_map<std::string, uint16_t> cacheObjects;
	std::vector<XMLobject> objects;

	bool loadXMLObject(const std::string& filePath);
	XMLobject& getObject(const std::string& nameObjects);
};