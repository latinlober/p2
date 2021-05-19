#include "Game.h"
#include "Platform/Platform.hpp"

int main(int argc, char** argv)
{
	util::Platform platform;
	std::string str_argv[10];
	// network parameters
	bool serverMode;
	bool clientMode;
	std::string remotePlayer;
	std::int16_t remotePort;

#if defined(_DEBUG)
	std::cout << "Start Tank Game with " << argc << " params!" << std::endl;
	for (int i = 0; i < argc; ++i)
	{
		std::cout << argv[i] << std::endl;
	}
#endif
	// parse cmd parameters
	if (argc == 1)
	{ // no parameters then default
		serverMode = true;
		clientMode = false;
		remotePlayer = "0.0.0.0";
		remotePort = 0;
	}
	else
	{
		for (int i = 0; i < argc; ++i)
		{
			str_argv[i].assign(argv[i]);
		}
		int res = str_argv[1].compare("serverMode");
		if (res == 0)
		{
			serverMode = true;
			clientMode = false;
			remotePlayer = "0.0.0.0";
			remotePort = 0;
		}
		res = str_argv[1].compare("clientMode");
		if (res == 0)
		{
			serverMode = false;
			clientMode = true;
			remotePlayer = str_argv[2];
			remotePort = stoi(str_argv[3]);
		}
	}
	std::srand(static_cast<unsigned>(time(NULL)));
	// init game engine
	Game mygame(serverMode, clientMode, remotePlayer, remotePort);

	// Get params

	// Start the game loop
	while (mygame.running())
	{

		mygame.update();

		mygame.render();
	}

	return EXIT_SUCCESS;

	return 0;
}
