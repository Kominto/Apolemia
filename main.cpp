#include "ECS.h"

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