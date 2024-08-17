#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include "graphics.h"
#include "map.h"
#include "player.h"

const int WIDTH = 680;
const int HEIGHT = 480;

class Game {
 private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	std::unique_ptr<Player> player;
	std::unique_ptr<Graphics> graphics;
	std::unique_ptr<Map> map;

 public:
	Game();
	~Game();
	void initialize();
	void destroy();
	void setup();
	void update();
	void processInput();
	void render();
	void run();
};
