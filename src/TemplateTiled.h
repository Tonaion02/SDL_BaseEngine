#pragma once

#include "PrecompiledHeaders.h"
#include "Format.h"





struct Property
{
public:
	Property() {}
	Property(const std::string& name, const std::string& type, const std::string& value)
		:name(name), type(type), value(value)
	{}

	std::string type;
	std::string name;
	std::string value;
};





struct TemplateObject
{
public:

	std::string name;
	std::vector<Property> properties;
};