#include "Image.h"




//------------------------------------------------------------------------------------
//Texture Class
//------------------------------------------------------------------------------------
uint16_t Texture::s_counterId = 0;


Texture::Texture(const std::string& path)
{
	SDL_Surface* temp = IMG_Load(path.c_str());
	m_w = temp->w;
	m_h = temp->h;
	m_path = path;

	m_rawTexture = SDL_CreateTextureFromSurface(SDL_Handler::get().getRenderer(), temp);
	SDL_FreeSurface(temp);

	m_id = s_counterId;
	s_counterId++;
}



Texture::Texture(SDL_Surface* surface)
	:m_w(surface->w), m_h(surface->h), m_path(""), m_rawTexture(SDL_CreateTextureFromSurface(SDL_Handler::get().getRenderer(), surface))
{
	m_id = s_counterId;
	s_counterId++;
}



uint32_t Texture::getW()
{
	return m_w;
}



uint32_t Texture::getH()
{
	return m_h;
}



std::string Texture::getPath()
{
	return m_path;
}



SDL_Texture* Texture::getRawTexture()
{
	return m_rawTexture;
}



uint16_t Texture::getId()
{
	return m_id;
}
//------------------------------------------------------------------------------------
//Texture Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//TextureLoader Class
//------------------------------------------------------------------------------------
int TextureHandler::loadTexture(const std::string& path)
{
	//Aggiungere assert path != ""

	for (int i = 0; i < s_textures.size(); i++)
	{
		if (s_textures[i].getPath() == path)
		{
			return i;
		}
	}

	s_textures.emplace_back(Texture(path));
	return s_textures.size() - 1;
}



int TextureHandler::getTextureIndex(uint16_t id)
{
	for (int i = 0; i < s_textures.size(); i++)
	{
		if (s_textures[i].getId() == id)
		{
			return i;
		}
	}

	//Aggiungere assert
	return -1;
}



int TextureHandler::loadTexture(SDL_Surface* surface)
{
	s_textures.emplace_back(Texture(surface));
	return s_textures.size() - 1;
}



Texture TextureHandler::getTexture(int index)
{
	return s_textures[index];
}
//------------------------------------------------------------------------------------
//TextureLoader Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Image Class
//------------------------------------------------------------------------------------
Image::Image(const std::string& path)
{
	m_indexTexture = TextureHandler::get().loadTexture(path);
	m_w = TextureHandler::get().getTexture(m_indexTexture).getW();
	m_h = TextureHandler::get().getTexture(m_indexTexture).getH();

	m_blendMode = SDL_BLENDMODE_BLEND;
}



Image::Image(uint32_t indexTexture)
	:m_indexTexture(indexTexture), 
	m_w(TextureHandler::get().getTexture(indexTexture).getW()), m_h(TextureHandler::get().getTexture(indexTexture).getH()),
	m_blendMode(SDL_BLENDMODE_BLEND)
{
	
}



Image::Image(SDL_Surface* surface)
{
	m_indexTexture = TextureHandler::get().loadTexture(surface);

	m_h = surface->h;
	m_w = surface->w;
	m_blendMode = SDL_BLENDMODE_BLEND;
}



uint32_t Image::getW()
{
	return m_w;
}



uint32_t Image::getH()
{
	return m_h;
}



uint32_t Image::getIndexTexture()
{
	return m_indexTexture;
}



void Image::blit(const Vector2i& pos) const
{
	SDL_Rect srcRect, destRect;
	
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_w;
	srcRect.h = m_h;

	destRect.x = pos.x;
	destRect.y = pos.y;
	destRect.w = m_w;
	destRect.h = m_h;

	SDL_RenderCopy(SDL_Handler::get().getRenderer(), TextureHandler::get().getTexture(m_indexTexture).getRawTexture(), &srcRect, &destRect);
}



void Image::blit(const Vector2i& pos, const Vector2i& startPos, const Vector2i& dimRect) const
{
	SDL_Rect srcRect, destRect;

	srcRect.x = startPos.x;
	srcRect.y = startPos.y;
	srcRect.w = dimRect.x;
	srcRect.h = dimRect.y;

	destRect.x = pos.x;
	destRect.y = pos.y;
	destRect.w = dimRect.x;
	destRect.h = dimRect.y;

	SDL_RenderCopy(SDL_Handler::get().getRenderer(), TextureHandler::get().getTexture(m_indexTexture).getRawTexture(), &srcRect, &destRect);
}



void Image::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetTextureBlendMode(TextureHandler::get().getTexture(m_indexTexture).getRawTexture(), blendMode);
}



void Image::setAlpha(float alpha)
{
	SDL_SetTextureAlphaMod(TextureHandler::get().getTexture(m_indexTexture).getRawTexture(), alpha * 255);
}
//------------------------------------------------------------------------------------
//Image Class
//------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------
//Surface Class
//------------------------------------------------------------------------------------
Surface::Surface(const std::string& path, uint32_t w, uint32_t h)
	:m_w(w), m_h(h)
{
	m_rawSurface = IMG_Load(path.c_str());
	SDL_SetSurfaceBlendMode(m_rawSurface, SDL_BLENDMODE_BLEND);

	if (w == 0 && h == 0)
	{
		m_w = m_rawSurface->w;
		m_h = m_rawSurface->h;
	}
}



Surface::Surface(const Color& color, uint32_t w, uint32_t h)
	:m_w(w), m_h(h)
{
	m_rawSurface = SDL_CreateRGBSurface(0, w, h, 32, 0xff, 0xff00, 0xff0000, 0xff000000);
	SDL_SetSurfaceBlendMode(m_rawSurface, SDL_BLENDMODE_BLEND);
}



uint32_t Surface::getW()
{
	return m_w;
}



uint32_t Surface::getH()
{
	return m_h;
}



SDL_Surface* Surface::getRawSurface()
{
	return m_rawSurface;
}



void Surface::setBlendMode(SDL_BlendMode blendMode)
{
	SDL_SetSurfaceBlendMode(m_rawSurface, blendMode);
}



void Surface::setAlpha(uint32_t alpha)
{
	SDL_SetSurfaceAlphaMod(m_rawSurface, alpha);
}



void Surface::blit(const Vector2i& pos, Surface& other) const
{
	SDL_Rect srcRect, destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = m_w;
	srcRect.h = m_h;

	destRect.x = pos.x;
	destRect.y = pos.y;
	destRect.w = m_w;
	destRect.h = m_h;

	SDL_BlitSurface(m_rawSurface, &srcRect, other.getRawSurface(), &destRect);
}



void Surface::blit(const Vector2i& pos, const Vector2i& startPos, const Vector2i& dim, Surface& other) const
{
	SDL_Rect srcRect, destRect;

	srcRect.x = startPos.x;
	srcRect.y = startPos.y;
	srcRect.w = dim.x;
	srcRect.h = dim.y;

	destRect.x = pos.x;
	destRect.y = pos.y;
	destRect.w = dim.x;
	destRect.h = dim.y;

	SDL_BlitSurface(m_rawSurface, &srcRect, other.getRawSurface(), &destRect);
}



void Surface::free()
{
	SDL_FreeSurface(m_rawSurface);
}
//------------------------------------------------------------------------------------
//Surface Class
//------------------------------------------------------------------------------------