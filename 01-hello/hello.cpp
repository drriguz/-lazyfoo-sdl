#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Surface* surface = NULL;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cerr << "SDL Init failed" << endl;
	}
	else
	{
		window = SDL_CreateWindow("Hello SDL", 
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				SCREEN_WIDTH,
				SCREEN_HEIGHT,
				SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			cerr << "Window could not be created!" << SDL_GetError() << endl;
		}
		else
		{
			surface = SDL_GetWindowSurface(window);
		    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
			SDL_UpdateWindowSurface(window);
			SDL_Delay(2000);
		}
	}
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

