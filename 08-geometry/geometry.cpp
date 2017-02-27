#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
SDL_Texture* loadTexture(const string& path);
bool loadImage(const string& path);
void draw();
void close();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

int x = 0;
int y = 0;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cerr << "Missing path argument" << endl;
		return 1;
	}
	string path = string(argv[1]);
	if(!init() || (texture = loadTexture(path)) == NULL )
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
			else if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_UP:
						y--;
						break;
					case SDLK_DOWN:
						y++;
						break;
					case SDLK_LEFT:
						x--;
						break;
					case SDLK_RIGHT:
						x++;
						break;
					default:
						break;
				}
				if(x < 0) x = 0;
				if(y < 0) y = 0;
				if(x >= SCREEN_WIDTH) x = SCREEN_WIDTH -  1;
				if(y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		draw();
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
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
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == NULL)
	{
		cerr << "Renderer could not be created!" << SDL_GetError() << endl;
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	if((IMG_Init(imgFlags) & imgFlags) != imgFlags)
	{
		cerr << "SDL image could not be initialized!" << IMG_GetError() << endl;
		return false;
	}
	return true;
}

SDL_Texture* loadTexture(const string& path)
{
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		cerr << "Image could not be loaded!" << SDL_GetError() << endl;
		return NULL;
	}
	newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	if(newTexture == NULL)
	{
		cerr << "Unable to optimize image!" << SDL_GetError();
	}
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

bool loadImage()
{
	texture = loadTexture("world.jpg");
	return texture != NULL;
}

void draw()
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
	cout << x << "," << y << endl;
	SDL_Rect rect = {x, y, 10, 10};
	SDL_RenderFillRect(renderer, &rect);
}

void close()
{

	SDL_DestroyTexture(texture);
	texture = NULL;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}
