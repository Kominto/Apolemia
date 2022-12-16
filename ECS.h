#ifndef ECS_H
#define ECS_H
#include <iostream>
#include <map>
#include <vector>
#include <any>
#include <functional>

uint32_t TID = 0;
uint32_t GETID () { return ++TID; }

struct Position{
	inline static uint32_t ID = GETID();
	int x, y;
};

struct Physic{
	inline static uint32_t ID = GETID();
	int vx, vy, a;
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

System UpdatePosition {Position::ID|Physic::ID, [](Entity & e){
		Position po = e.GET<Position>();
		Physic py = e.GET<Physic>();
		po.x += py.vx;
		po.y += py.vy;
		py.vx += py.a;
		py.vy += py.a;
		e.SET<Position>(po);
		e.SET<Physic>(py);
	}
};

System Display {Position::ID, [](Entity & e){
		Position po = e.GET<Position>();
		std::cout<<"Position of entity: "<<po.x<<";"<<po.y<<std::endl;
	}
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

