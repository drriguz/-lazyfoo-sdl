#include <iostream>
#include <string>
#include "texture.h"
#include "sdlsys.h"

int main(int argc, char* argv[])
{
	SdlSystem system("ColorKey", 640, 480);	
	if(!system.init())
	{
		std::cerr << "Init failed!" << std::endl;
		return 1;
	}
	system.run();
	return 0;
}
