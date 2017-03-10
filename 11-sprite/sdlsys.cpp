#include "sdlsys.h"
#include "texture.h"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SdlSystem::SdlSystem(const std::string& name, int width, int height)
	:_window(NULL), _renderer(NULL), _name(name),_width(width), _height(height), _background(NULL), _foo(NULL)
{
}

SdlSystem::~SdlSystem()
{
	this->deinit();
	if(this->clips != NULL)
	{
		delete[] this->clips;
		this->clips = NULL;
	}
}

bool SdlSystem::init()
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
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
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

	_background = new Texture(_renderer);
	_foo = new Texture(_renderer);
	return true;
}

void SdlSystem::deinit()
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

	if(_background != NULL)
	{
		delete _background;
		_background = NULL;
	}
	if(_foo != NULL)
	{
		delete _foo;
		_foo = NULL;
	}
	IMG_Quit();
	SDL_Quit();
}

bool SdlSystem::loadMedia()
{
	if(!_background->loadFromFile("background.png")
		|| !_foo->loadFromFile("sprites.png"))
	{
		std::cerr <<" Failed to load resources" << std::endl;
		return false;
	}
	if(this->clips != NULL)
	{
		delete[] this->clips;
		this->clips = NULL;
	}
	this->clips = new SDL_Rect[4];
	clips[0] = {0, 0, 100, 100};
	clips[1] = {100, 0, 100, 100};
	clips[2] = {0, 100, 100, 100};
	clips[3] = {100, 100, 100, 100};
	return true;
}

void SdlSystem::run()
{
	bool quit = false;
	SDL_Event e;
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
			SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(_renderer);
			this->_background->render(0, 0);

			this->_foo->render(0, 0, &(this->clips[0]));
			this->_foo->render(0, 200, &(this->clips[1]));
			this->_foo->render(200, 0, &(this->clips[2]));
			this->_foo->render(200, 200, &(this->clips[3]));
			SDL_RenderPresent(_renderer);
		}
		SDL_Delay(20);
	}
}















