#pragma once

#include "PrecompiledHeaders.h"

#include "Math/Vector.h"





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

protected:
	Options() {}

protected:
	std::string filePath;

	Vector2i tileDimension;
	Vector2i screenDimension;
	//Non so se va bene o può funzionare
	Vector2i zoom;
};