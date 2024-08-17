#include "map.h"
#include "logger.h"
#include "vec2.h"

void Map::addWall(Wall wall) { walls.push_back(wall); }

int Map::loadMap() {

	walls.push_back(Wall(Vec2(5, 5), Vec2(100, 5)));
	walls.push_back(Wall(Vec2(100, 5), Vec2(100, 50)));
	walls.push_back(Wall(Vec2(5, 5), Vec2(5, 50)));
	walls.push_back(Wall(Vec2(5, 50), Vec2(100, 50)));
	
	return 0;
}

void Map::renderMap(std::unique_ptr<Graphics> &graphics) {
	for (Wall& wall : walls) {
		graphics->drawLine(wall.src.x, wall.src.y, wall.dst.x, wall.dst.y, 0xFFFF0000);
	}
}
