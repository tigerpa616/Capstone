#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

// vvv-SUMMARY OF EVERYTHING IN THIS HEADER FILE -vvv //
//Basically, he's got a Manager which holds entities, which are anything drawn in your game.
//Each entity has components, which give it functionality.
//Each component has it's own class, so templates and other fancy stuff are required in order to get and add components.

/*
This is a bit of a jump in the learning curve! Basically, the ECS idea lets you organise memory so that it can be passed to the CPU in the most efficient way. 
The way a CPU accesses memories uses a few levels of caching (L1, L2 etc) with L1 being the smallest but the closest to the CPU (so, the fastest). 
It is most expensive to read from RAM, so arranging things so they can be passed in little contiguous chunks reduces 'cache misses'.
*/


class Component;
class Entity; //Will be used to keep track of the components

using ComponentID = std::size_t; //What we are saying here is that ComponentID is size_t

inline ComponentID getComponentID()
{
	static ComponentID lastID = 0; //everytime we call this lastID will remeber what it last was
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getComponentID(); //will generate a new lastID for us and put it in our typeID
	return typeID;
}

constexpr std::size_t maxComponents = 32; //the maximum number of components an entity can hold

using ComponentBitSet = std::bitset<maxComponents>; //used for checking to make sure the component is right, by generating a bit set and comparing it to the component and if they match dope!
using ComponentArray = std::array<Component*, maxComponents>; //just an array component pointers

class Component
{
public:
	Entity* entity;

	virtual void initialize() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool EntitiyIsActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;

public: 
	void update()
	{
		for (auto& c : components) c->update();
		
	}

	void draw() { for (auto& c : components) c->draw(); }
	bool isActive() const { return EntitiyIsActive; }
	void destroy() { EntitiyIsActive = false; } //On any given component we can call destroy it will find our unactive entities in the game and removes them

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>]; //will check if we have the component attached
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c; //when we add a position it is always placed in the same place in the array
		componentBitSet[getComponentTypeID<T>()] = true;

		c->initialize();
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;

public: 
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}
	void refresh() //Will remove entitites if not active
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};