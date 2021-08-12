#pragma once

#include "SDLHandler.h"

#include "Image.h"

#include "Math/Vector.h"





class Font
{
public:
	Font() {}
	Font(const std::string& filePath, uint16_t size, const Color& color);

	TTF_Font* getRawFont();
	uint16_t getId();
	std::string getFilePath();
	Vector2i getSize();

	void blit(const Vector2i& pos, const std::string& letter) const;

private:
	TTF_Font* m_rawFont;

	std::string m_filePath;
	uint16_t m_id;

	Image m_image;

	Vector2i m_size;
	Color color;

	static uint16_t s_counterId;
	static std::string s_alphabet;
};





class FontHandler
{
public:
	static FontHandler& get()
	{
		static FontHandler instance;
		return instance;
	}

	int loadFont(const std::string& filePath, uint16_t size);
	int getFontIndex(uint16_t id);
	int getFontIndex(const std::string& filePath);

	Font& getFont(int index);

protected:
	FontHandler() {}

protected:
	std::vector<Font> s_fontes;
};





class TextRendering
{
public:
	TextRendering() {}
	TextRendering(uint16_t indexFont);

	void blit(const Vector2i& pos);
	void update(const std::string& text);

private:
	uint16_t m_indexFont;

	std::string m_text;
};