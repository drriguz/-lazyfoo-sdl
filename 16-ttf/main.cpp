#include <iostream>
#include <string>
#include "texture.h"
#include "game.h"

int main(int argc, char* argv[])
{
	Game game("ColorKey", 640, 480);	
	if(!game.init() || !game.loadMedia())
	{
		std::cerr << "Init failed!" << std::endl;
		return 1;
	}
	game.run();
	return 0;
}
