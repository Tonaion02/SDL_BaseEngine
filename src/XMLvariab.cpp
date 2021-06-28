#include "XMLvariab.h"





//------------------------------------------------------------------------------------
//XMLvariab Class
//------------------------------------------------------------------------------------
XMLvariab::XMLvariab(const std::string& line)
{
	std::string newline = removeFrontSpace(line);
	std::vector<std::string> infoAboutLine = split(newline, " ");
	
	//Take name from element
	name = remove(infoAboutLine[0], "<");
	//Take name from element

	//Eliminate "<nameElement" from infoAboutLine
	infoAboutLine.erase(infoAboutLine.begin());
	//Eliminate "<nameElement" from infoAboutLine

	if (infoAboutLine.size() > 0)
	{
		//Eliminate "/>" from last element
		if (isInString(infoAboutLine[infoAboutLine.size() - 1], ">"))
		{
			infoAboutLine[infoAboutLine.size() - 1] = remove(infoAboutLine[infoAboutLine.size() - 1], ">");
		}

		if (isInString(infoAboutLine[infoAboutLine.size() - 1], "/"))
		{
			infoAboutLine[infoAboutLine.size() - 1] = remove(infoAboutLine[infoAboutLine.size() - 1], "/");
		}
		//Eliminate "/>" from last element

		//Take the value and the key(name) from the line
		std::string value;
		std::string key;
		for (auto info : infoAboutLine)
		{
			value = removeQuotationMarks(stride(info, "="));
			key = stride(info, 0, findInString(info, "="));
			values[key] = value;
		}
		//Take the value and the key(name) from the line
	}
}



std::string XMLvariab::getValue(const std::string& key)
{
	//AGGIUNGERE ASSERT
	//if (values.find(key) == values.end());

	return values[key];
}
//------------------------------------------------------------------------------------
//XMLvariab Class
//------------------------------------------------------------------------------------