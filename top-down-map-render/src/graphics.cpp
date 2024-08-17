#include "graphics.h"
#include "logger.h"

Graphics::Graphics(int width, int height) {
	this->width = width;
	this->height = height;
	this->pixels = new Pixel[width * height];
}

Graphics::~Graphics() {
	delete pixels;
}

void Graphics::clear() {
	for (int i = 0; i < width * height; i++) {
		pixels[i] = 0xFF000000;
	}
}

void Graphics::drawPixel(int x, int y, Pixel pixel) {
	pixels[(width * y) + x] = pixel;
}

void Graphics::drawRect(int x, int y, int w, int h, Color color) {
	for (int i = x; i < x + w; i += 1) {
		for (int j = y; j < y + h; j += 1) {
			drawPixel(i, j, color);
		}
	}
}

// Draw a line
// Digital Differential Analyzer algorithm
void Graphics::drawLine(int x0, int y0, int x1, int y1, Color color) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int step = dx >= dy ? dx : dy;

	dx = dx / step;
	dy = dy / step;

	int x = x0;
	int y = y0;

	for (int i = 0; i <= step; i += 1) {
		drawPixel(x, y, color);
		x += dx;
		y += dy;
	}
	
	// int m = dy / dx;
	// for (int x = x0; x <= x1; x++) {
	// 	int y = m * (x - x1) + y1;
	// 	drawPixel(x, y, color);
	// }
}

Pixel* Graphics::getBuffer() { return pixels; }

int Graphics::getWidth() { return width; }

int Graphics::getHeight() { return height; }
