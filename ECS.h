#ifndef ECS_H
#define ECS_H
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <any>
#include <string>
#include <functional>
#include <tuple>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace APP {
	SDL_Window * WIN;
	SDL_Renderer * REN;
	SDL_Texture * TEX;
	SDL_Event EVE;
	bool run;
	int INIT(){
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		WIN = SDL_CreateWindow("Hey!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
		REN = SDL_CreateRenderer(WIN, -1, 0);
		TEX = IMG_LoadTexture(REN, "sprite.png");
		run = true;
		return 0;
	}
	void CLEAN(){
		SDL_DestroyTexture(TEX);
		SDL_DestroyRenderer(REN);
		SDL_DestroyWindow(WIN);
		IMG_Quit();
		SDL_Quit();
	}
}

uint32_t TID = 1;
uint32_t GETID () { 
	TID *= 2;
	return TID; }


struct Position{
	inline static uint32_t ID = GETID();
	float x, y;
};


struct Physic{
	inline static uint32_t ID = GETID();
	float vx, vy;
};


struct Sprite{
	inline static uint32_t ID = GETID();
	float x, y, h, w;
	int sx, sy, sh, sw;
};


struct Movement{
	inline static uint32_t ID = GETID();
	float v;
};

std::map<std::string,uint32_t> TS = {{"Position",Position::ID}, {"Physic",Physic::ID},
	{"Sprite", Sprite::ID}, {"Movement", Movement::ID}};

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
		return std::make_from_tuple<T>(CONTENT[T::ID]);
	}
};

struct System {
	uint32_t MASK;
	std::function<void(Entity & e)> DO;
	void check (std::vector<Entity> & E) {
		for (auto & e: E){
			if((MASK&e.MASK)==MASK) DO(e);
		}
	}
};

System UpdatePosition {Position::ID|Physic::ID, [](Entity & e){
	Position po = e.GET<Position>();
	Physic py = e.GET<Physic>();
	po.x += py.vx;
	po.y += py.vy;
	py.vx *= 0.98;
	py.vy *= 0.98;
	e.SET<Physic>(py);
	e.SET<Position>(po);
}};

System UpdateSprite {Position::ID|Sprite::ID, [](Entity & e){
	Position p = e.GET<Position>();
	Sprite s = e.GET<Sprite>();
	s.x = p.x;
	s.y = p.y;
	e.SET<Sprite>(s);
}};

System Display {Sprite::ID, [](Entity & e){
	Sprite s = e.GET<Sprite>();
	SDL_Rect src = {s.sx,s.sy,s.sh,s.sw};
	SDL_FRect dst = {s.x,s.y,s.h,s.w};
	SDL_RenderCopyF(APP::REN, APP::TEX, &src, &dst);
}};

System MoveLeft {Movement::ID|Physic::ID, [](Entity & e){
	Physic p = e.GET<Physic>();
	Movement m = e.GET<Movement::ID>();
	p.vx -= m.v;
	e.SET<Physic>(p);	
}};

System MoveRight {Movement::ID|Physic::ID, [](Entity & e){
	Physic p = e.GET<Physic>();
	Movement m = e.GET<Movement>();
	p.vx += m.v;
	e.SET<Physic>(p);
}};

System MoveUp {Movement::ID|Physic::ID, [](Entity & e){
	Physic p = e.GET<Physic>();
	Movement m = e.GET<Movement>();
	p.vy -= m.v;
	e.SET<Physic>(p);
}};

System MoveDown {Movement::ID|Physic::ID, [](Entity & e){
	Physic p = e.GET<Physic::ID>();
	Movement m = e.GET<Movement::ID>();
	p.vy += m.v;
	e.SET<Physic>(p);
}};

struct View{
	std::vector<Entity> ENTITIES;
	void ProcessEvent(){
		std::cout<<"Processing events..."<<std::endl;
		switch(APP::EVE.type) {
			case SDL_KEYDOWN:
				switch (APP::EVE.key.keysym.sym)
				{
					case SDLK_LEFT:
						MoveLeft.check(ENTITIES);
						break;
					case SDLK_RIGHT:
						MoveRight.check(ENTITIES);
						break;
					case SDLK_UP:
						MoveUp.check(ENTITIES);
						break;
					case SDLK_DOWN:
						MoveDown.check(ENTITIES);
						break;
					default: break;
				}
				break;
			default: break;
		
		}
	}
	void Update () {
		UpdatePosition.check(ENTITIES);
		UpdateSprite.check(ENTITIES);
		Display.check(ENTITIES);
	}
};
#endif

