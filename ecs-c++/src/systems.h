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
			const auto entityId = entity.getId();
			auto& transform = registry->getComponent<TransformComponent>(entity);

			transform.x += 1;
			transform.y += 1;
		}
	}
};
