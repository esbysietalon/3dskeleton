#include "stdafx.h"
#include "Core.h"


Core::Core(Skeleton* s)
{
	frame = s;
	init();
}
Core::~Core()
{
}
void Core::update() {
	camera->generateView(actors, pixels);
	for (int i = 0; i < actors.size(); i++) {
		actors.at(i)->move();
	}

	frame->removeSprite(screen);
	frame->removeTexture(screenTexture);
	screenTexture = frame->createTexture(pixels, sw, sh);
	screen = frame->createSprite(screenTexture, 0, 0);
}
double Core::rand() {
	std::uniform_real_distribution<double> dist(0, 1);

	return dist(*rng);
}
void Core::init() {
	//player generation
	rng = new std::mt19937(std::random_device()());
	

	actors.emplace_back(new Actor(0, 0));
	int player = actors.size() - 1;
	
	int* playerTexture = new int[100 * 100];
	for (int i = 0; i < 100 * 100; i++) {
		playerTexture[i] = 0x2222FF;
	}

	int points = 3 + (int)(10 * rand());
	

	sw = frame->getScreenDim().x;
	sh = frame->getScreenDim().y;
	
	for (int i = 0; i < points; i++) {
		int rx = (int)(sw * rand());
		int ry = (int)(sh * rand());
		actors.at(player)->addFramePoint(pos(rx, ry));
	}	

	registerControls(player);
	
	
	camera = new Camera(sw, sh);
	pixels = new int[sw * sh];

	memset(pixels, 0x000000, sw * sh * sizeof(int));

	screenTexture = frame->createTexture(pixels, sw, sh);
	screen = frame->createSprite(screenTexture, 0, 0);
}


void Core::updateMousePosition() {
	int mousex = 0;
	int mousey = 0;
	SDL_GetMouseState(&mousex, &mousey);
	camera->updateMousePosition(mousex, mousey);
}

void Core::left() {
	camera->move(move_t::LEFT);
}
void Core::right() {
	camera->move(move_t::RIGHT);
}
void Core::up() {
	camera->move(move_t::UP);
}
void Core::down() {
	camera->move(move_t::DOWN);
}
/*
void Core::left() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::LEFT, true);
	}
}
void Core::right() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::RIGHT, true);
	}
}

void Core::nleft() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::LEFT, false);
	}
}
void Core::nright() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::RIGHT, false);
	}
}
void Core::nup() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::UP, false);
	}
}
void Core::ndown() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::DOWN, false);
	}
}
void Core::front() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::FRONT, true);
	}
}
void Core::nfront() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::FRONT, false);
	}
}
void Core::back() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::BACK, true);
	}
}
void Core::nback() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::BACK, false);
	}
}
*/
void Core::registerControls(int player)
{
	//std::cout << actors.at(player).getPos().x << " " << actors.at(player).getPos().y << " " << actors.at(player).getPos().z << " " << std::endl;
	controlled.emplace_back(player);
}
