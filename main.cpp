#include "ECS.h"

System UpdatePosition;
UpdatePosition.MASK = Position::ID | Physic::ID;
UpdatePosition.DO = [&](Entity e){
	Position po = e.GET<Position>();
	Physic py = e.GET<Physic>();
	po.x += py.vx;
	po.y += py.vy;
	py.vx += py.a;
	py.vy += py.a;
	e.SET<Position>(po);
	e.SET<Physic>(py);
}

System Display;
Display.MASK = Position::ID;
Display.DO = [&](Entity e){
	Position po = e.GET<Position>();
	std::cout<<"Position of entity: "<<po.x<<";"<<po.y<<std::endl;
}

int main () {
	View V;
	V.SYSTEMS.push_back(UpdatePosition);
	V.SYSTEMS.push_back(Display);
	V.ENTITIES.push_back(Entity());
	V.ENTITIES.push_back(Entity());
	V.ENTITIES[0].ADD<Position>();
	V.ENTITIES[0].ADD<Physic>();
	V.ENTITIES[1].ADD<Position>();

	V.ENTITIES[0].SET<Position>(Position{0,0});
	V.ENTITIES[0].SET<Physic>(Physic{1,1,1});
	V.ENTITIES[1].SET<Position>(Position{0,0});

	V.APPLY();
	return 0;
}