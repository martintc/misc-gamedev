#include <cstdlib>
#include <iostream>

#include "game.h"
#include "logger.h"

int main(int argc, char **argv) {
	Logger::info("Starting program");

	Game game;
	game.initialize();
	game.setup();
	game.run();
	game.destroy();
	
	return EXIT_SUCCESS;
}
