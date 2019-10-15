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

	std::function<void()> updateMousePosition = std::bind(&Core::updateMousePosition, *core);

	frame->registerFunction(l, SDL_KEYDOWN, SDL_SCANCODE_A);
	frame->registerFunction(r, SDL_KEYDOWN, SDL_SCANCODE_D);
	frame->registerFunction(u, SDL_KEYDOWN, SDL_SCANCODE_R);
	frame->registerFunction(d, SDL_KEYDOWN, SDL_SCANCODE_F);

	frame->registerFunction(updateMousePosition, SDL_MOUSEMOTION, SDL_SCANCODE_A);
}

int main(int arg, char** argv) {
	Skeleton frame(800, 600, "2D Direct");
	Core core(&frame);
	
	frame.addRunFunc(std::bind(&Core::update, core));

	registerControls(&core, &frame);
	
	while (frame.listen() > 0) {
		frame.run();
	}
	return 0;
}
