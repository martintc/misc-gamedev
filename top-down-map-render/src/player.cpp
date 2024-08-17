#include "player.h"
#include "logger.h"

Player::Player(Vec2 position, Vec2 scale, Color color) {
	Logger::info("Creating plyer.");
	this->position = position;
	this->scale = scale;
	this->color = color;
}

Player::~Player() { Logger::info("Destroying player."); }

void Player::render(std::unique_ptr<Graphics> &graphics) {
	graphics->drawRect(position.x, position.y, scale.x, scale.y, color);
}
