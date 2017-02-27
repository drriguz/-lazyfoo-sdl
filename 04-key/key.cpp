#include <iostream>
#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
bool loadImage();
void close();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imageSurface = NULL;

int main(int argc, char* argv[])
{
	if(!init() || !loadImage())
	{
		cerr << "Failed to initialize!" << endl;
		return 1;
	}
	
	bool quit = false;
	SDL_Event e;
	while(!quit)
	{
		while(SDL_PollEvent(&e) != 0)
		{
			if(e.type == SDL_QUIT)
			{
				cout << "Bye" << endl;
				quit = true;
			}
			else if(e.key.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						cout << "^" << endl;
						break;
					case SDLK_DOWN:
						cout << "|" << endl;
						break;
					case SDLK_LEFT:
						cout << "<" << endl;
						break;
					case SDLK_RIGHT:
						cout << ">" << endl;
						break;
					default:
						break;
				}
			}
		}

		SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}
	close();

	return 0;
}

bool init()
{
	if(!SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL could not initialize!" << SDL_GetError() << endl;
		return false;
	}
	window = SDL_CreateWindow("Hello SDL Image",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		cerr << "Window could not be created!" << SDL_GetError() << endl;
		return false;
	}
	screenSurface = SDL_GetWindowSurface(window);
	return true;
}

bool loadImage()
{
	imageSurface = IMG_Load("world.jpg");
	if(imageSurface == NULL)
	{
		cerr << "Image could not be loaded!" << SDL_GetError() << endl;
		return false;
	}
	return true;
}

void close()
{
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
