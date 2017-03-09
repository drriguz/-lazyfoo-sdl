#ifndef _SDL_SYSTEM_H_
#define _SDL_SYSTEM_H_

#include <string>

struct SDL_Window;
struct SDL_Renderer;

class SdlSystem
{
	public:
		SdlSystem(const std::string& name, int width, int height);
		~SdlSystem();
	public:
		bool init();
		void deinit();
		void run();
		SDL_Renderer* getRenderer(){ return this->_renderer; }
		SDL_Window* getWindow(){ return this->_window; }
		int getScreenWidth(){ return this->_width; }
		int getScreenHeight(){ return this->_height; }
	private:
		std::string _name;
		int _width;
		int _height;
		SDL_Window* _window;
		SDL_Renderer* _renderer;
};

#endif
