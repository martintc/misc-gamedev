#pragma once

#include <cstdint>
#include "common.h"

class Graphics {
 private:
	int width;
	int height;
	Pixel* pixels;

 public:
	Graphics(int width, int height);
	~Graphics();
	void clear();
	void drawPixel(int x, int y, Pixel pixel);
	void drawRect(int x, int y, int w, int h, Color color);
	void drawLine(int x0, int y0, int x1, int y1, Color color);
	Pixel* getBuffer();
	int getWidth();
	int getHeight();
};
