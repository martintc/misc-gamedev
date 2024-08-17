#pragma once

#include "graphics.h"
#include "vec2.h"
#include <list>
#include <memory>

struct Wall {
	Vec2 src;
	Vec2 dst;

	Wall(Vec2 src, Vec2 dst) {
		this->src = src;
		this->dst = dst;
	}

	Wall(int x0, int y0, int x1, int y1) {
		this->src.x = x0;
		this->src.y = y0;
		this->dst.x = x1;
		this->dst.y = y1;
	}
};

class Map {
 private:
	std::list<Wall> walls;
	
 public:
	Map() = default;
	~Map() = default;
	int loadMap(std::string path);
	void addWall(Wall wall);
	void renderMap(std::unique_ptr<Graphics> &graphics);
};

