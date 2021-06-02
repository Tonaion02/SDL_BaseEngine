#include "TemplateTiled.h"





//------------------------------------------------------------------------------------
//Property Class
//------------------------------------------------------------------------------------
Property::Property(const std::string& propertyLine)
{
	std::vector<std::string> infoAboutProperty = split(propertyLine, " ");

	for (auto info : infoAboutProperty)
	{
		if (isInString(info, "name="))
		{
			name = removeQuotationMarks(stride(info, "name="));
		}
		else if (isInString(info, "type="))
		{
			type = removeQuotationMarks(stride(info, "type="));
		}
		else if (isInString(info, "value="))
		{
			info = remove(info, "/");
			info = remove(info, ">");
			value = removeQuotationMarks(stride(info, "value="));
		}
	}
}
//------------------------------------------------------------------------------------
//Property Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//CacheObjectHandler Class
//------------------------------------------------------------------------------------
bool CacheTemplateObjectHandler::loadTemplateObject(const std::string& nameTemplate)
{
	//Search name from the already loaded
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].name == nameTemplate)
		{
			return false;
		}
	}
	//Search name from the already loaded



	std::vector<std::string> templateLines = getlines("data/levels/" + nameTemplate);
	std::string& line = templateLines[0];

	TemplateObject templateObject;
	//Set name in base at name of template
	templateObject.name = nameTemplate;

	//Load Property
	for (int i = 0; i < templateLines.size(); i++)
	{
		line = templateLines[i];

		if (isInString(line, "<property"))
		{
			line = removeFrontSpace(line);
			Property property = Property(line);
			templateObject.properties.push_back(property);
		}

	}
	//Load Property

	objects.push_back(templateObject);
	return true;
}



TemplateObject CacheTemplateObjectHandler::getTemplateObject(const std::string& nameTemplate)
{
	//Add Template to the Cache System
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].name == nameTemplate)
		{
			return objects[i];
		}
	}
	//Add Template to the Cache System

	//Aggiungere assert quando non si trova il templateObject
}
//------------------------------------------------------------------------------------
//CacheObjectHandler Class
//------------------------------------------------------------------------------------