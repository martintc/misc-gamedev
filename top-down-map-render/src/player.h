#pragma once

#include <memory>
#include "vec2.h"
#include "common.h"
#include "graphics.h"

class Player {
 private:
	Vec2 position;
	Vec2 scale;
	Color color;

 public:
	Player(Vec2 position, Vec2 scale, Color color);
	~Player();
	void render(std::unique_ptr<Graphics> &graphics);
};

