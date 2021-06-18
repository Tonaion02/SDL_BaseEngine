#pragma once

#include "PrecompiledHeaders.h"

#include "Format.h"

#include "Math/Vector.h"

#include "XMLvariab.h"





class Options
{
public:
	static Options& get()
	{
		static Options instance;
		return instance;
	}
	
	void Init(const std::string& filePath);

	std::string getFilePath() const;
	std::string getFilePath(const std::string& nameFilePath);

	Vector2i getScreenDimension() const;
	bool isVsync() const;

	uint8_t getFps() const;
	void setFps(uint8_t fps);

protected:
	Options() {}

protected:
	std::string s_optionsFilePath;

	Vector2i s_tileDimension;
	Vector2i s_screenDimension;
	//Non so se va bene o può funzionare
	Vector2i s_zoom;

	bool s_vsync;
	uint8_t s_fps;

	//Per ogni nome un value
	std::unordered_map<std::string, std::string> s_filePaths;
};