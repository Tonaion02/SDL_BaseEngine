#pragma once

#include "PrecompiledHeaders.h"
#include "Math/Vector.h"

#include "SDLHandler.h"





struct Color
{
public:
	uint32_t r, g, b, a;

	Color() {}
	Color(uint32_t r, uint32_t g, uint32_t b, uint32_t a) : r(r), g(g), b(b), a(a) {}
};





class Texture
{
public:
	Texture() {}
	Texture(const std::string& path);
	Texture(SDL_Surface* surface);

	uint32_t getW();
	uint32_t getH();

	std::string getPath();
	SDL_Texture* getRawTexture();
private:
	uint32_t m_w, m_h;

	std::string m_path;
	SDL_Texture* m_rawTexture;

	static int32_t s_counter;
};





class TextureHandler
{
public:
	static TextureHandler& get()
	{
		static TextureHandler instance;
		return instance;
	}

	int loadTexture(const std::string& path);
	int loadTexture(SDL_Surface* surface);
	Texture getTexture(int index);

protected:
	TextureHandler() {}

private:
	std::vector<Texture> m_textures;
};





class Image
{
public:
	Image() {}
	Image(const std::string& path);
	Image(uint32_t indexTexure);
	Image(SDL_Surface* src);

	uint32_t getW();
	uint32_t getH();
	uint32_t getIndexTexture();

	void blit(const Vector2i& pos);
	void blit(const Vector2i& pos, const Vector2i& startRect, const Vector2i& dimRect);

	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(uint32_t alpha);

private:
	uint32_t m_w, m_h;

	uint32_t m_indexTexture;

	SDL_BlendMode m_blendMode;
};





class Surface
{
public:
	Surface() {}
	Surface(const std::string& path, uint32_t w=0, uint32_t h=0);
	Surface(const Color& color, uint32_t w, uint32_t h);

	uint32_t getW();
	uint32_t getH();
	SDL_Surface* getRawSurface();

	void blit(const Vector2i& pos, Surface& other);

	void setBlendMode(SDL_BlendMode blendMode);
	void setAlpha(uint32_t alpha);

	void free();

private:
	uint32_t m_w, m_h;
	SDL_Surface* m_rawSurface;
};