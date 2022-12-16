#ifndef ECS_H
#define ECS_H
#include <iostream>
#include <map>
#include <vector>
#include <any>
#include <functional>
#include <SDL2/SDL.h>

uint32_t TID = 0;
uint32_t GETID () { return ++TID; }

struct Position{
	inline static uint32_t ID = GETID();
	int x, y;
};

struct Physic{
	inline static uint32_t ID = GETID();
	float vx, vy, a;
};

struct Sprite{
	inline static uint32_t ID = GETID();
	SDL_Renderer * r;
};

struct Entity{
	uint32_t MASK = 0;
	std::map<uint32_t, std::any> CONTENT;
	template <typename T>
	void ADD () {
		MASK |= T::ID;
		CONTENT[T::ID] = {0};
	}
	template <typename T>
	void REMOVE () {
		MASK &= T::ID;
		CONTENT.erase(T::ID);
	}
	template <typename T>
	void SET (T t) {
		CONTENT[T::ID] = t;
	}
	template <typename T>
	T GET () {
		return std::any_cast<T>(CONTENT[T::ID]);
	}
};

struct System {
	uint32_t MASK;
	std::function<void(Entity & e)> DO;
};

struct View{
	std::vector<Entity> ENTITIES;
	std::vector<System> SYSTEMS;
	void APPLY () {
		for (auto & e: ENTITIES) {
			for (auto s: SYSTEMS)
				if ((s.MASK & e.MASK) == s.MASK) s.DO(e);
		}
	}
};
#endif

