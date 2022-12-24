#include "ECS.h"

int main () {
	APP::INIT();
	View V;
	std::string line, view, value;
	std::any A;
	std::ifstream FILE;
	FILE.open("FILE");
	V.ENTITIES.push_back(Entity());
	while(std::getline(FILE, line)){
		std::istringstream token(line);
		std::getline(token, view, ':');
		V.ENTITIES[0].MASK |= TS[view];
		std::cout<<"Added component "<<TS[view]<<" to entity"<<std::endl;
		while(std::getline(token, value, ',')){
			A = std::tuple_cat(std::make_tuple(A), std::make_tuple(value));
			std::cout<<"Added value "<<value<<" to component"<<std::endl;
		}
		V.ENTITIES[0].CONTENT[TS[view]] = A;
	}
	FILE.close();
	std::cout<<"New entity created!"<<std::endl;
	while(APP::run){
		SDL_PollEvent(&APP::EVE);
		if (APP::EVE.type == SDL_QUIT) APP::run = false;
		V.ProcessEvent();
		SDL_RenderClear(APP::REN);
		V.Update();
		SDL_RenderPresent(APP::REN);
	}
	APP::CLEAN();
	return 0;
}
