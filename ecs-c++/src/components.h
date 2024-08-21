#pragma once

#include "ecs.h"

struct TestComponent {
 public:
	int x;

	TestComponent(int x = 0) {
		this->x = x;
	}
};

struct AnotherTestComponent {
public:
	int y;

	AnotherTestComponent(int y = 0) {
		this->y = y;
	}
	
};

struct TransformComponent {
	int x;
	int y;

	TransformComponent(int x = 0, int y = 0) {
		this->x = x;
		this->y = y;
	}
};
