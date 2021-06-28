#include "XMLobject.h"





//------------------------------------------------------------------------------------
//XMLobject Struct
//------------------------------------------------------------------------------------
XMLobject::XMLobject(const std::string& filePath)
{
	name = filePath;

	//Load XML Object from file
	std::vector<std::string> lines = getlines(filePath);

	std::string& line = lines[0];
	XMLvariab var = XMLvariab();
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];
		if (!isInString(line, "xml"))
		{
			if (isInString(line, "/>"))
			{
				var = XMLvariab(line);
				xmlVariabs.push_back(var);
				var = XMLvariab();
			}
			else
			{
				var.withRawData = true;
				var.rawData.push_back(line);
			}
		}
	}
	//Load XML Object from file
}



//------------------------------------------------------------------------------------
//XMLobject Struct
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//CacheXML Struct
//------------------------------------------------------------------------------------
XMLobject& CacheXML::getObject(const std::string& nameObjects)
{
	return objects[cacheObjects[nameObjects]];
}



bool CacheXML::loadXMLObject(const std::string& filePath)
{
	//da aggiustare
	std::string nameObject;

	for (int i = 0; i < objects.size(); i++)
	{
		if (nameObject == objects[i].name)
		{
			return false;
		}
	}

	std::vector<std::string> lines = getlines(filePath);

	std::string& line = lines[0];
	XMLobject object;
	object.name = nameObject;
	for (int i = 0; i < lines.size(); i++)
	{
		line = lines[i];

		object.xmlVariabs.push_back(XMLvariab(line));
	}

	objects.push_back(object);
	cacheObjects[nameObject] = objects.size() - 1;

	return true;
}
//------------------------------------------------------------------------------------
//CacheXML Struct
//------------------------------------------------------------------------------------