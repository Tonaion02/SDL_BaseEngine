#include "Options.h"




//------------------------------------------------------------------------------------
//Options Class
//------------------------------------------------------------------------------------
void Options::Init(const std::string& filePath)
{
	s_optionsFilePath = filePath;
	std::vector<std::string> optionsLines = getlines(filePath);
	
	std::string& line = optionsLines[0];
	for (int i = 0; i < optionsLines.size(); i++)
	{
		line = optionsLines[i];
		if (isInString(line, "<window"))
		{
			XMLvariab var = XMLvariab(line);
			s_screenDimension.x = std::stoi(var.getValue("width"));
			s_screenDimension.y = std::stoi(var.getValue("height"));
		}
		else if (isInString(line, "<filepath"))
		{
			XMLvariab var = XMLvariab(line);
			s_filePaths[var.getValue("name")] = var.getValue("value");
		}
		else if (isInString(line, "<vsync"))
		{
			XMLvariab var = XMLvariab(line);
			s_vsync = fromStringToBool(var.getValue("value"));

		}
	}
}



std::string Options::getFilePath() const
{
	return s_optionsFilePath;
}



std::string Options::getFilePath(const std::string& nameFilePath)
{
	//assert se non trovi il nameFilePath
	return s_filePaths[nameFilePath];
}



Vector2i Options::getScreenDimension() const
{
	return s_screenDimension;
}



bool Options::isVsync() const
{
	return s_vsync;
}



uint8_t Options::getFps() const
{
	return s_fps;
}



void Options::setFps(uint8_t fps)
{
	if (!s_vsync)
	{
		s_fps = fps;
	}
}
//------------------------------------------------------------------------------------
//Options Class
//------------------------------------------------------------------------------------