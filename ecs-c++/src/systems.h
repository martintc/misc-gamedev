#pragma once

#include "ecs.h"
#include "logger.h"
#include "components.h"

class TestSystem: public System {
 public:
	TestSystem() {
		requireComponent<TransformComponent>();
	}

	void Update() {
		for (auto entity : getEntities()) {
			
		}
	}
};
