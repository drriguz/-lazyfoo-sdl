#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>
#include <inttypes.h>
#include <SDL2/SDL.h>

class Texture
{
	public:
		Texture(SDL_Renderer* renderer);
		~Texture();
	public:
		bool loadFromFile(const std::string& path);
		void free();
		void setColor(uint8_t r, uint8_t g, uint8_t b);
		void setBlendMode(SDL_BlendMode blending);
		void setAlpha(uint8_t alpha);
		void render(int x, int y, SDL_Rect* clip = NULL);
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;
		int _width;
		int _height;
};

#endif
