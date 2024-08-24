#include "ecs.h"
#include "components.h"
#include "systems.h"
#include "logger.h"
#include <memory>
#include <bitset>
#include <typeinfo>

#include <iostream>

void entityTests() {
	Logger::info("Performing Entity Tests");
	
	std::unique_ptr<Registry> registry = std::make_unique<Registry>();

	Entity entity = registry->createEntity();

	Logger::info("Entity created with id: " + std::to_string(entity.getId()));

	Logger::info("Completed performing Entity Test");
}

void componentTests() {
	Logger::info("Performing Component Test");

	auto componentId = Component<TransformComponent>::getId();
	Logger::info("Component Id for Transform Component: " + std::to_string(componentId));
	componentId = Component<TestComponent>::getId();
	Logger::info("Component Id for Test Component: " + std::to_string(componentId));
	componentId = Component<TransformComponent>::getId();
	Logger::info("Component Id for Transform Component: " + std::to_string(componentId));
	
	Logger::info("Completed performing Component Test");
}

void entityComponentTests() {
	Logger::info("Performing Entitiy Component Test");

	std::unique_ptr<Registry> registry = std::make_unique<Registry>();

	Entity entity = registry->createEntity();
	Logger::info("Created an Entity with id: " + std::to_string(entity.getId()));
	registry->addComponent<TransformComponent>(entity, TransformComponent(0, 0));
	Logger::info("Added a Transform Component to Entity with id: " + std::to_string(entity.getId()));
	bool result = registry->hasComponent<TransformComponent>(entity);
	Logger::info("Entitiy with id " + std::to_string(entity.getId()) + " has a Transform Component: " + (result ? "true" : "false"));
	registry->removeComponent<TransformComponent>(entity);
	Logger::info("Remocing Transform Component");
	result = registry->hasComponent<TransformComponent>(entity);
	Logger::info("Entitiy with id " + std::to_string(entity.getId()) + " has a Transform Component: " + (result ? "true" : "false"));

	Entity entity2 = registry->createEntity();
	Logger::info("Creating an Entity with id: " + std::to_string(entity2.getId()));
	registry->addComponent<TestComponent>(entity2, TestComponent(1));
	Logger::info("Add a Test Component to Entity with id: " + std::to_string(entity2.getId()));

	Logger::info("Testing if both entities have a Test Component");
	result = registry->hasComponent<TestComponent>(entity);
	Logger::info(std::to_string(entity.getId()) + " : " + (result ? "true" : "false"));
	result = registry->hasComponent<TestComponent>(entity2);
	Logger::info(std::to_string(entity2.getId()) + " : " + (result ? "true" : "false"));
	
	Logger::info("Entity Component Tests complete");
}

void systemEntityTest() {
	Logger::info("Performing System Entity Test");

	std::unique_ptr<Registry> registry = std::make_unique<Registry>();
	Entity entity = registry->createEntity();
	const auto entityId = entity.getId();
	Logger::info("Created Entity with id " + std::to_string(entityId));
	System system;
	Logger::info("Create a system");

	auto entities = system.getEntities();
	Logger::info("Number of entities in system: " + std::to_string(entities.size()));

	system.addEntityToSystem(entity);
	Logger::info("Adding entity to system");
	entities = system.getEntities();
	Logger::info("Number of entities in system: " + std::to_string(entities.size()));
	system.removeEntityFromSystem(entity);
	Logger::info("Removing entity from system");
	entities = system.getEntities();
	Logger::info("Number of entities in system: " + std::to_string(entities.size()));
	
	Logger::info("Completed System Entity Test");
}

void systemRegistryTests() {
	Logger::info("Performing System Registry Tests");

	Logger::info("Completed System Registry Test");
}

int main(int argc, char* argv[]) {
	Logger::info("Starting program.");
	Logger::info("");

	entityTests();
	Logger::info("");
	componentTests();
	Logger::info("");
	entityComponentTests();
	Logger::info("");
	systemEntityTest();
	Logger::info("");
	systemRegistryTests();
	
	
	Logger::info("");
	Logger::info("Ending program.");
	return EXIT_SUCCESS;
}
