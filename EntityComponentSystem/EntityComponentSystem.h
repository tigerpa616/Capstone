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
class Manager;

using ComponentID = std::size_t; //What we are saying here is that ComponentID is size_t

using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u; //everytime we call this lastID will remeber what it last was
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID(); //will generate a new lastID for us and put it in our typeID
	return typeID;
}

constexpr std::size_t maxComponents = 32; //the maximum number of components an entity can hold
constexpr std::size_t maxGroups = 32; //we can have a maximum of 32 groups, we can use these groups as render layers

using ComponentBitSet = std::bitset<maxComponents>; //used for checking to make sure the component is right, by generating a bit set and comparing it to the component and if they match dope!
using GroupBitset = std::bitset<maxGroups>;
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
	Manager& manager;
	bool EntitiyIsActive = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitset groupBitset;

public: 
	Entity(Manager& mManager) : manager(mManager) {}

	void update()
	{
		for (auto& c : components) c->update();
	}

	void draw() { for (auto& c : components) c->draw(); }
	bool isActive() const { return EntitiyIsActive; }
	void destroy() { EntitiyIsActive = false; } //On any given component we can call destroy it will find our unactive entities in the game and removes them

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup]; //will return true or false if a certain bit is zero or one in that bitset
	}

	void addGroup(Group mGroup);

	void deleteGroup(Group mGroup)
	{
		groupBitset[mGroup] = false; //we will use this to check in the manager to see if the entity is false and if it is it will remove it
	}

	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()]; //will check if we have the component attached
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
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;


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
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), std::end(v), [i](Entity* mEntity)
				{
					return !mEntity->isActive() || !mEntity->hasGroup(i);
				}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup)
	{
		groupedEntities[mGroup].emplace_back(mEntity);//will add entity to the group
	}

	std::vector<Entity*>& getGroup(Group mGroup)
	{
		return groupedEntities[mGroup];
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};