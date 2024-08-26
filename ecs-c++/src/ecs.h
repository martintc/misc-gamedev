#pragma once

#include <algorithm>
#include <bitset>
#include <cstdint>
#include <memory>
#include <queue>
#include <set>
#include <stack>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "logger.h"

const unsigned int MAXCOMPONENTS = 64;

using Signature = std::bitset<MAXCOMPONENTS>;

/***************************
 ** Entity
***************************/

class Entity {
private:
	int id;

public:
	Entity(int id) {
		this->id = id;
	}

	void Kill() {
		// TODO
	}
	
	int getId() const {
		return id;
	}

	// Operator overloads
	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& other) const { return id == other.id; }
	bool operator >(const Entity& other) const { return id > other.id; }
	bool operator <(const Entity& other) const { return id < other.id; }
};

/***************************
 ** Component
***************************/

struct IComponent {
 protected:
	static int nextId;
};

template <typename TComponent>
class Component: public IComponent {
 public:
	static int getId() {
		static auto id = nextId++;
		return id;
	}
};

int IComponent::nextId = 0;


class IComponentPool {
 public:
	virtual ~IComponentPool() {}
};

template <typename T>
class ComponentPool: public IComponentPool {
 private:
	std::vector<T> data;

 public:
	ComponentPool(int size = 100) {
		data.resize(100);
	}

	virtual ~ComponentPool() = default;

	bool isEmpty() const {
		return data.empty();
	}

	int getSize() const {
		return data.size();
	}

	void resize(int n) {
		data.resize(n);
	}

	void clear() {
		data.clear();
	}

	void set(int index, T object) {
		data[index] = object;
	}

	T& get(Entity entity) {
		// return static_cast<T&>(data[index]);
		return static_cast<T&>(data[entity.getId()]);
	}

	T& operator [](unsigned int index) {
		return data[index];
	}
};

/***************************
 ** System
***************************/

class System {
private:
	Signature systemSignature;
	std::vector<Entity> entities;
	
public:
	System() = default;
	~System() = default;
	class Registry* registry;
	
	void addEntityToSystem(Entity entity) {
		entities.push_back(entity);
	}
	
	void removeEntityFromSystem(Entity entity) {
	  entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	}
	
	std::vector<Entity> getEntities() const {
		return entities;
	}
	
	const Signature& getSignature() const {
		return systemSignature;
	}
	
	template <typename TComponent>
	void requireComponent() {
		const auto componentId = Component<TComponent>::getId();

		systemSignature.set(componentId, true);
	}
};

/***************************
 ** Registry
***************************/

class Registry {
private:
	unsigned int entityCount = 0;
	std::set<Entity> entitiesToAdd;
	std::set<Entity> entitiesToRemove;
	std::vector<Signature> entitySignatures;
	std::deque<unsigned int> freeEntities;
	std::vector<std::shared_ptr<IComponentPool>> componentPools;
	std::unordered_map<std::type_index, std::shared_ptr<System>> systems;

public:
	Registry() = default;
	~Registry() = default;

	void update() {
		// TODO
		// Add Entity to relevant system
	}

  /***********************
	 ** Entity management
	***********************/
	Entity createEntity() {
		int entityId;
		
		if (freeEntities.size() > 0) {
			entityId = freeEntities.front();
			freeEntities.pop_front();
		} else {
			entityId = entityCount;
			entityCount += 1;
		}

		Entity entity(entityId);

		if (entityId >= entitySignatures.size()) {
			entitySignatures.resize(entityId += 1);
		}

		entitySignatures[entityId].set(0);

		entitiesToAdd.insert(entity);

		return entity;
	}

	void destroyEntity(Entity entity) {
		// TODO
	}

	/***********************
	 ** Component management
	***********************/
	// Add a component to an entity
	template <typename TComponent, typename ...TArgs>
	void addComponent(Entity entity, TArgs&& ...args) {
		const auto entityId = entity.getId();
		const auto componentId = Component<TComponent>::getId();

		if (componentId >= static_cast<int>(componentPools.size())) {
			componentPools.resize(componentId + 1, nullptr);
		}

		std::shared_ptr<ComponentPool<TComponent>> pool;

		// check if pool exists
		if (!componentPools[componentId]) {
			// make pool
			pool = std::make_shared<ComponentPool<TComponent>>();
			componentPools[componentId] = pool;
		}

		pool = std::static_pointer_cast<ComponentPool<TComponent>>(componentPools[componentId]);

		if (entityId >= pool->getSize()) {
			pool->resize(entityCount);
		}

		// Create component to go into pool
		TComponent component(std::forward<TArgs>(args)...);

		// add component to pool
		pool->set(entityId, component);

		entitySignatures[entityId].set(componentId, true);
	}

	// Remove a component from an entity
	template <typename TComponent>
	void removeComponent(Entity entity) {
		const auto entityId = entity.getId();
		const auto componentId = Component<TComponent>::getId();

		// Set the entitie's bit position for component to false
		entitySignatures[entityId].set(componentId, false);
	}

	// Check to see if an entity has a component
	// This is done by testing the component's bit position
	template <typename TComponent>
	bool hasComponent(Entity entity) {
		const auto entityId = entity.getId();
		const auto componentId = Component<TComponent>::getId();

		return entitySignatures[entityId].test(componentId);
	}

	template <typename TComponent>
	TComponent& getComponent(Entity entity) {
		const auto entityId = entity.getId();
		const auto componentId = Component<TComponent>::getId();
		auto pool = std::static_pointer_cast<ComponentPool<TComponent>>(componentPools[componentId]);
		return pool->get(entityId);
	}

	/***********************
	 ** System management
	***********************/
	template <typename TSystem, typename ...TArgs>
	void addSystem(TArgs&& ...args) {
		// TODO args
		const auto id = std::type_index(typeid(TSystem));
		std::shared_ptr<TSystem> system = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
		system->registry = this;
		systems.insert({ id, system });
	}

	template <typename TSystem>
	void removeSystem() {
		const auto system = systems.find(std::type_index(typeid(TSystem)));
		systems.erase(system);
	}

	template <typename TSystem>
	bool hasSystem() const {
		return systems.count(std::type_index(typeid(TSystem)));
	}

	template <typename TSystem>
	TSystem& getSystem() const {
		const auto id = std::type_index(typeid(TSystem));
		const auto system = systems.find(id);
		return *(std::static_pointer_cast<TSystem>(system->second));
	}

	template <typename TSystem>
	void addEntityToSystem(Entity entity) {
		const auto system = systems.find(std::type_index(typeid(TSystem)))->second;
		system->addEntityToSystem(entity);
	}

	template <typename TSystem>
	void removeEntityFromSystem(Entity entity) {
		const auto system = systems.find(std::type_index(typeid(TSystem)))->second;
		system->removeEntityFromSystem(entity);
	}
};
