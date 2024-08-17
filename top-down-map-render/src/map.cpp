#include "map.h"
#include "logger.h"
#include "vec2.h"
#include <fstream>

void Map::addWall(Wall wall) { walls.push_back(wall); }

int Map::loadMap(std::string path) {

	// walls.push_back(Wall(Vec2(5, 5), Vec2(100, 5)));
	// walls.push_back(Wall(Vec2(100, 5), Vec2(100, 50)));
	// walls.push_back(Wall(Vec2(5, 5), Vec2(5, 50)));
	// walls.push_back(Wall(Vec2(5, 50), Vec2(100, 50)));

	Logger::info("Loading map");

	std::ifstream file;
	file.open(path);

	int n0 = 0;
	int x0 = 0;
	int y0 = 0;
	int x1 = 0;
	int y1 = 0;

	if (!(file >> n0)) {
		Logger::info("Could not read first line.");
		return -1;
	}

	Logger::info("Number of walls: " + std::to_string(n0) + ".");

	while(file >> x0 >> y0 >> x1 >> y1) {
		Logger::info("Line (" + std::to_string(x0) + "," + std::to_string(y0) + "), (" + std::to_string(x1) + "," + std::to_string(y1) + ").");
		addWall(Wall(Vec2(x0, y0), Vec2(x1, y1)));
	}
	
	file.close();
	
	return 0;
}

void Map::renderMap(std::unique_ptr<Graphics> &graphics) {
	for (Wall& wall : walls) {
		graphics->drawLine(wall.src.x, wall.src.y, wall.dst.x, wall.dst.y, 0xFFFF0000);
	}
}
