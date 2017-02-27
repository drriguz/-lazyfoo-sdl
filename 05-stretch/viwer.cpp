#include <iostream>
#include <SDL2/SDL.h>
#include <string>

#include <SDL2/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
SDL_Surface* loadImage(const string& path);
void close();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imageSurface = NULL;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cerr << "Missing path argument" << endl;
		return 1;
	}
	string path = string(argv[1]);
	if(!init() || (imageSurface = loadImage(path)) == NULL )
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

		SDL_Rect stretchRect;
		stretchRect.x = 0;
		stretchRect.y = 0;
		stretchRect.w = SCREEN_WIDTH;
		stretchRect.h = SCREEN_HEIGHT;
		SDL_BlitScaled(imageSurface, NULL, screenSurface, &stretchRect);
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

SDL_Surface* loadImage(const string& path)
{
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		cerr << "Image could not be loaded!" << SDL_GetError() << endl;
		return NULL;
	}
	optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, NULL);
	if(optimizedSurface == NULL)
	{
		cerr << "Unable to optimize image!" << SDL_GetError();
	}
	SDL_FreeSurface(loadedSurface);
	return optimizedSurface;
}

void close()
{
	SDL_FreeSurface(imageSurface);
	imageSurface = NULL;

	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}
