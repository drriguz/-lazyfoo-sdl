#include "texture.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Texture::Texture(SDL_Renderer* renderer)
:_texture(NULL),_width(0),_height(0),_renderer(renderer)
{
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(const std::string& path)
{
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		std::cerr << "Failed to load image " << path.c_str() << ":" << IMG_GetError() << std::endl;
		return false;
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
	newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
	if(newTexture == NULL)
	{
		std::cerr << "Failed to create texture:" << SDL_GetError() << std::endl;
		return false;
	}
	_width = loadedSurface->w;
	_height = loadedSurface->h;
	SDL_FreeSurface(loadedSurface);
	_texture = newTexture;
	return true;
}

void Texture::free()
{
	if(_texture == NULL)
		return;
	SDL_DestroyTexture(_texture);
	_texture = NULL;
	_width = 0;
	_height = 0;
}

void Texture::render(int x, int y)
{
	SDL_Rect renderQuad = {x, y, _width, _height};
	SDL_RenderCopy(_renderer, _texture, NULL, &renderQuad);
}

int Texture::getWidth()
{
	return _width;
}

int Texture::getHeight()
{
	return _height;
}


