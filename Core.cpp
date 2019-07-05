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
	memset(pixels, 0xFFFFFF, sw * sh * sizeof(int));
	for (int i = 0; i < actors.size(); i++) {
		actors.at(i)->move();

		int ax = actors.at(i)->getPos().x;
		int ay = actors.at(i)->getPos().y;

		int aw = actors.at(i)->getDim().x;
		int ah = actors.at(i)->getDim().y;

		for (int y = ay; y < ay + ah; y++)
			for (int x = ax; x < ax + aw; x++)
				pixels[x + y * sw] = actors.at(i)->getPixels()[(x-ax) + (y-ay) * aw];
	}
	frame->removeSprite(screen);
	frame->removeTexture(screenTexture);
	screenTexture = frame->createTexture(pixels, sw, sh);
	screen = frame->createSprite(screenTexture, 0, 0);
}

void Core::init() {

	//player generation
	actors.emplace_back(new Actor(200, 200, 0));
	int player = actors.size() - 1;
	
	int* playerTexture = new int[100 * 100];
	for (int i = 0; i < 100 * 100; i++) {
		playerTexture[i] = 0x2222FF;
	}

	actors.at(player)->setSprite(playerTexture, 100, 100);
	registerControls(player);
	//end

	sw = frame->getScreenDim().x;
	sh = frame->getScreenDim().y;
	pixels = new int[sw * sh];

	memset(pixels, 0x000000, sw * sh * sizeof(int));

	screenTexture = frame->createTexture(pixels, sw, sh);
	screen = frame->createSprite(screenTexture, 0, 0);
	

}


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
void Core::up() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::UP, true);
	}
}
void Core::down() {
	for (int i = 0; i < controlled.size(); i++) {
		actors.at(controlled.at(i))->push(move_t::DOWN, true);
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

void Core::registerControls(int player)
{
	//std::cout << actors.at(player).getPos().x << " " << actors.at(player).getPos().y << " " << actors.at(player).getPos().z << " " << std::endl;
	controlled.emplace_back(player);
}
