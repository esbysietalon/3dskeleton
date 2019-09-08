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
	std::function<void()> f = std::bind(&Core::front, *core);
	std::function<void()> b = std::bind(&Core::back, *core);
	std::function<void()> rotl = std::bind(&Core::rotl, *core);
	std::function<void()> rotr = std::bind(&Core::rotr, *core);

	/*std::function<void()> nl = std::bind(&Core::nleft, *core);
	std::function<void()> nr = std::bind(&Core::nright, *core);
	std::function<void()> nu = std::bind(&Core::nup, *core);
	std::function<void()> nd = std::bind(&Core::ndown, *core);
	std::function<void()> nf = std::bind(&Core::nfront, *core);
	std::function<void()> nb = std::bind(&Core::nback, *core);
*/
	frame->registerFunction(l, SDL_KEYDOWN, SDL_SCANCODE_A);
	frame->registerFunction(r, SDL_KEYDOWN, SDL_SCANCODE_D);
	frame->registerFunction(f, SDL_KEYDOWN, SDL_SCANCODE_W);
	frame->registerFunction(b, SDL_KEYDOWN, SDL_SCANCODE_S);
	frame->registerFunction(u, SDL_KEYDOWN, SDL_SCANCODE_R);
	frame->registerFunction(d, SDL_KEYDOWN, SDL_SCANCODE_F);
	frame->registerFunction(rotl, SDL_KEYDOWN, SDL_SCANCODE_Q);
	frame->registerFunction(rotr, SDL_KEYDOWN, SDL_SCANCODE_E);

	/*frame->registerFunction(nl, SDL_KEYUP, SDL_SCANCODE_A);
	frame->registerFunction(nr, SDL_KEYUP, SDL_SCANCODE_D);
	frame->registerFunction(nf, SDL_KEYUP, SDL_SCANCODE_W);
	frame->registerFunction(nb, SDL_KEYUP, SDL_SCANCODE_S);*/
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
