#include "TextRendering.h"





//------------------------------------------------------------------------------------
//Font Class
//------------------------------------------------------------------------------------
uint16_t Font::s_counterId = 0;
std::string Font::s_alphabet = "abcdefghilmnopqrstuvwxyz0123456789:";



Font::Font(const std::string& filePath, uint16_t size, const Color& color)
	:m_id(s_counterId), m_filePath(filePath)
{
	//Assert for controll the filePath

	//Assert for size

	s_counterId++;

	SDL_Color textColor = { color.r, color.g, color.b, color.a };

	m_rawFont = TTF_OpenFont(filePath.c_str(), size);
	
	SDL_Surface* surface = TTF_RenderText_Solid(m_rawFont, s_alphabet.c_str(), textColor);
	m_size = { surface->w / (uint16_t)(s_alphabet.size()), surface->h };

	m_image = Image(surface);
	
	SDL_FreeSurface(surface);
}



TTF_Font* Font::getRawFont()
{
	return m_rawFont;
}



uint16_t Font::getId()
{
	return m_id;
}



std::string Font::getFilePath()
{
	return m_filePath;
}



Vector2i Font::getSize()
{
	return m_size;
}



void Font::blit(const Vector2i& pos, const std::string& letter) const
{
	//Assert per controllare se letter ha size = 1

	int index;

	if (letter == " ")
	{
		return;
	}

	for (int i = 0; i < s_alphabet.size(); i++)
	{
		if (s_alphabet[i] == letter[0])
		{
			index = i;
		}
	}

	m_image.blit(pos, { index * m_size.x, 0 }, { m_size.x, m_size.y });
	//m_image.blit(pos);
}
//------------------------------------------------------------------------------------
//Font Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//FontHandler Class
//------------------------------------------------------------------------------------
int FontHandler::loadFont(const std::string& filePath, uint16_t size)
{
	for (int i = 0; i < s_fontes.size(); i++)
	{
		if (s_fontes[i].getFilePath() == filePath)
		{
			return i;
		}
	}

	s_fontes.emplace_back(Font(filePath, size, Color(0, 0, 0, 0)));
	return s_fontes.size() - 1;
}



int FontHandler::getFontIndex(uint16_t id)
{
	//Assert per controllare validità id

	for (int i = 0; i < s_fontes.size(); i++)
	{
		if (s_fontes[i].getId() == id)
		{
			return i;
		}
	}



	//Se non trova alcun font con quel id
	return -1;
}



int FontHandler::getFontIndex(const std::string& filePath)
{
	//assert per controllare filePath

	for (int i = 0; i < s_fontes.size(); i++)
	{
		if (s_fontes[i].getFilePath() == filePath)
		{
			return i;
		}
	}
	


	//Se non trova alcun font con quel id
	return -1;
}



Font& FontHandler::getFont(int index)
{
	//assert index value
	return s_fontes[index];
}
//------------------------------------------------------------------------------------
//FontHandler Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//TextRendering Class
//------------------------------------------------------------------------------------
TextRendering::TextRendering(uint16_t indexFont)
{
	//Assert per controllare indexFont

	m_indexFont = indexFont;
}



void TextRendering::blit(const Vector2i& pos)
{
	for (int i = 0; i < m_text.size(); i++)
	{
		std::string letter = m_text.substr(i, 1);
		Vector2i p = { pos.x + (FontHandler::get().getFont(m_indexFont).getSize().x * i), pos.y };
		FontHandler::get().getFont(m_indexFont).blit(
			p,
			letter);
	}
}



void TextRendering::update(const std::string& text)
{
	m_text = text;
}
//------------------------------------------------------------------------------------
//TextRendering Class
//------------------------------------------------------------------------------------