#include <iostream>
#include <SDL2/SDL.h>

#define USING_SDL_IMAGE

#ifdef USING_SDL_IMAGE
#include <SDL2/SDL_image.h>
#endif

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
	SDL_BlitSurface(imageSurface, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

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
#ifdef USING_SDL_IMAGE
	imageSurface = IMG_Load("world.jpg");
#else
	imageSurface = SDL_LoadBMP("hello.bmp");
#endif
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

	SDL_Quit();
}
