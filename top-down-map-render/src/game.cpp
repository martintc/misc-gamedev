#include "game.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include "graphics.h"
#include "logger.h"

Game::Game() { isRunning = true; }

Game::~Game() {}

void Game::initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		isRunning = false;
		Logger::error("Could not initialize SDL.");
		return;
	}

	window = SDL_CreateWindow(NULL, WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);

	if (!window) {
		isRunning = false;
		Logger::error("Could not create SDL Window.");
		return;
	}

	renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
		isRunning = false;
		Logger::error("Could not create SDL Renderer.");
		return;
	}

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

	if (!texture) {
		isRunning = false;
		Logger::error("Could not create SDL Texture.");
		return;
	}

	graphics = std::make_unique<Graphics>(WIDTH, HEIGHT);
	map = std::make_unique<Map>();
	player = std::make_unique<Player>(Vec2(10, 10), Vec2(4, 4), 0xFF0000FF);
}

void Game::destroy() {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::setup() {
	map->loadMap("./assets/test.map");
}

void Game::update() {}

void Game::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_EVENT_KEY_DOWN: {
			if (event.key.key == SDLK_ESCAPE) {
				isRunning = false;
				return;
			}
		}
		}
	}
}

void Game::render() {
	graphics->clear();
	SDL_RenderClear(renderer);
	
	map->renderMap(graphics);
	player->render(graphics);

	// upate texture
	Pixel* buffer = graphics->getBuffer();
	int width = graphics->getWidth();

	SDL_UpdateTexture(texture, NULL, buffer, width * sizeof(Pixel));
	SDL_RenderTexture(renderer, texture, NULL, NULL);
	
	SDL_RenderPresent(renderer);
}

void Game::run() {
	while (isRunning) {
		processInput();
		update();
		render();
	}
}
