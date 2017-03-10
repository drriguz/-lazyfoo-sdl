#include "game.h"
#include "texture.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Game::Game(const std::string& name, int width, int height)
	:_window(NULL), _renderer(NULL), _name(name),_width(width), _height(height), _background(NULL), _foo(NULL)
{
}

Game::~Game()
{
	this->deinit();
	if(this->clips != NULL)
	{
		delete[] this->clips;
		this->clips = NULL;
	}
}

bool Game::init()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Failed to initialize SDL:" << SDL_GetError() << std::endl;
		return false;
	}
	if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cerr << "Warning: Linear texture filtering not enabled!" << std::endl;
	}
	_window = SDL_CreateWindow(this->_name.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			this->_width,
			this->_height,
			SDL_WINDOW_SHOWN);
	if(_window == NULL)
	{
		std::cerr << "Window could not be created:" << SDL_GetError() << std::endl;
		return false;
	}
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(_renderer == NULL)
	{
		std::cerr << "Renderer could not be created:" << SDL_GetError() << std::endl;
		return false;
	}
	SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		std::cerr << "SDL image could not be initialized!" << IMG_GetError() << std::endl;
		return false;
	}

	this->_background.setRenderer(this->_renderer);
	this->_foo.setRenderer(this->_renderer);
	return true;
}

void Game::deinit()
{
	if(_renderer != NULL)
	{
		SDL_DestroyRenderer(_renderer);
		_renderer = NULL;
	}
	if(_window != NULL)
	{
		SDL_DestroyWindow(_window);
		_window = NULL;
	}

	IMG_Quit();
	SDL_Quit();
}

bool Game::loadMedia()
{
	if(!_background.loadFromFile("background.png")
			|| !_foo.loadFromFile("bear.png"))
	{
		std::cerr <<" Failed to load resources" << std::endl;
		return false;
	}
	this->_foo.setBlendMode(SDL_BLENDMODE_BLEND);
	if(this->clips != NULL)
	{
		delete[] this->clips;
		this->clips = NULL;
	}
	this->clips = new SDL_Rect[4];
	clips[0] = {0, 0, 85, 128};
	clips[1] = {85, 0, 85, 128};
	clips[2] = {170, 0, 85, 128};
	clips[3] = {255, 0, 85, 128};
	return true;
}

void Game::run()
{
	bool quit = false;
	uint8_t r = 255, g = 255, b = 255;
	uint8_t alpha = 255;
	int frame = 0;
	int x = 100, y = 200;
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	double angle = 0.0d;
	SDL_Event e;
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			else if(e.type == SDL_KEYDOWN)
			{
				int step = 8;
				switch(e.key.keysym.sym)
				{
					case SDLK_q:
						r += step;
						break;
					case SDLK_a:
						r -= step;
						break;
					case SDLK_w:
						g += step;
						break;
					case SDLK_s:
						g -= step;
						break;
					case SDLK_e:
						b += step;
						break;
					case SDLK_d:
						b -= step;
						break;
					case SDLK_r:
						alpha += step;
						break;
					case SDLK_f:
						alpha -= step;
						break;
					case SDLK_LEFT:
						x -= 2;
						flipType = SDL_FLIP_NONE;
						angle = 0.0d;
						break;
					case SDLK_RIGHT:
						flipType = SDL_FLIP_HORIZONTAL;
						angle = 360.0d;
						x += 2;
						break;
					default:
						break;
				}
			}
		}
		SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(_renderer);
		this->_foo.setColor(r, g, b);
		this->_background.render(0, 0);
		this->_background.setAlpha(alpha);

		SDL_Rect* currentClip = &this->clips[frame / 4];
		this->_foo.render(x, y, currentClip, angle, NULL, flipType);

		SDL_RenderPresent(_renderer);
		++frame;
		if(frame / 4 >= 4)
			frame = 0;
		SDL_Delay(20);
	}
}
