#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <string>

struct SDL_Texture;
struct SDL_Renderer;

class Texture
{
	public:
		Texture(SDL_Renderer* renderer);
		~Texture();
	public:
		bool loadFromFile(const std::string& path);
		void free();
		void render(int x, int y);
		int getWidth();
		int getHeight();
	private:
		SDL_Texture* _texture;
		SDL_Renderer* _renderer;
		int _width;
		int _height;
};

#endif
