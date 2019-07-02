// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Skeleton.h"
#include "Core.h"
#include "Actor.h"

void registerControls(Core* core, Skeleton* frame) {
	std::function<void()> l = std::bind(&Core::left, *core);
	std::function<void()> r = std::bind(&Core::right, *core);
	std::function<void()> u = std::bind(&Core::up, *core);
	std::function<void()> d = std::bind(&Core::down, *core);

	std::function<void()> nl = std::bind(&Core::nleft, *core);
	std::function<void()> nr = std::bind(&Core::nright, *core);
	std::function<void()> nu = std::bind(&Core::nup, *core);
	std::function<void()> nd = std::bind(&Core::ndown, *core);

	frame->registerFunction(l, SDL_KEYDOWN, SDL_SCANCODE_A);
	frame->registerFunction(r, SDL_KEYDOWN, SDL_SCANCODE_D);
	frame->registerFunction(u, SDL_KEYDOWN, SDL_SCANCODE_W);
	frame->registerFunction(d, SDL_KEYDOWN, SDL_SCANCODE_S);

	frame->registerFunction(nl, SDL_KEYUP, SDL_SCANCODE_A);
	frame->registerFunction(nr, SDL_KEYUP, SDL_SCANCODE_D);
	frame->registerFunction(nu, SDL_KEYUP, SDL_SCANCODE_W);
	frame->registerFunction(nd, SDL_KEYUP, SDL_SCANCODE_S);
}

int main(int arg, char** argv) {
	Skeleton frame(800, 600, "3D Demo");
	Core core(&frame);
	
	frame.addRunFunc(std::bind(&Core::update, core));

	registerControls(&core, &frame);
	
	while (frame.listen() > 0) {
		frame.run();
	}
	return 0;
}
