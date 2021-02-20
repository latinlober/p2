#include "Game.h"
#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	std::srand(static_cast<unsigned>(time(NULL)));
	// init game engine
	Game mygame;

	// Create the main window

	// Load a sprite to display
	/*
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    */

	// Start the game loop
	while (mygame.running())
	{

		mygame.update();

		mygame.render();
	}

	return EXIT_SUCCESS;

	return 0;
}
