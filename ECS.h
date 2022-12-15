#include <iostream>
#include <map>
#include <vector>
#include <any>

uint32_t TID = 0;
template <typename T>
uint32_t GETID () { return ++TID; }

struct Position{
	inline static uint32_t ID = GETID<Position>();
	int x, y;
};

struct Physic{
	inline static uint32_t ID = GETID<Physic>();
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

uint32_t MASK = Position::ID | Physic::ID;
void DO(Entity e) {
	Position po = e.GET<Position>();
	Physic py = e.GET<Physic>();
	po.x += py.vx;
	po.y += py.vy;
	py.vx += py.a;
	py.vy += py.a;
	e.SET<Position>(po);
	e.SET<Physic>(py);
}

struct View{
	std::vector<Entity> CONTENT;
	void SELECT () {
		for (auto e: CONTENT) {
			if ((MASK & e.MASK) == MASK) DO(e);
		}
	}
};


