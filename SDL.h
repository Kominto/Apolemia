#ifndef SDL_H
#define SDL_H
#include "ECS.h"
#include <SDL2/SDL.h>

namespace APP {
	SDL_Window * WIN;
	SDL_Renderer * REN;
	SDL_Event EVE;
	bool run;
	View V;
	int INIT(){
		SDL_Init(SDL_INIT_EVERYTHING);
		WIN = SDL_CreateWindow("Hey!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
		REN = SDL_CreateRenderer(WIN, -1, 0);
		run = true;
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
		return 0;
	}
	void LOOP(){
		while(run){
			while(SDL_PollEvent(&EVE)){
				if (EVE.type == SDL_QUIT) run=false;
			}
			SDL_RenderClear(REN);
			SDL_RenderPresent(REN);
			V.APPLY();
		}
	}
	void QUIT(){
		SDL_DestroyRenderer(REN);
		SDL_DestroyWindow(WIN);
		SDL_Quit();
	}
}
#endif