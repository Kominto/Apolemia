#include "ECS.h"

int main () {
	View V;
	Position p1, p2;
	V.CONTENT.push_back(Entity());
	V.CONTENT.push_back(Entity());
	V.CONTENT[0].ADD<Position>();
	V.CONTENT[0].ADD<Physic>();
	V.CONTENT[1].ADD<Position>();

	V.CONTENT[0].SET<Position>(Position{0,0});
	V.CONTENT[0].SET<Physic>(Physic{1,1,1});
	V.CONTENT[1].SET<Position>(Position{0,0});

	for (int i = 0; i<4; i++){
		V.SELECT();
		p1 = V.CONTENT[0].GET<Position>();
		p2 = V.CONTENT[1].GET<Position>();
		std::cout<<"Position of E1: "<<p1.x<<";"<<p1.y<<std::endl;
		std::cout<<"Position of E2: "<<p2.x<<";"<<p2.y<<std::endl;
	}
	return 0;
}