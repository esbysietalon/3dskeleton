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
	for (int i = 0; i < actors.size(); i++) {
		//std::cout << "updating " << i << std::endl;
		actors.at(i)->move();
		//actors.at(i).push(move_t::RIGHT, true);
		//std::cout << "actor " << i << " is at (" << actors.at(i)->getPos().x << ", " << actors.at(i)->getPos().y << ", " << actors.at(i)->getPos().z << ")" << std::endl;
		
		frame->getSprite(actors.at(i)->getSprite())->x = actors.at(i)->getPos().x;
		frame->getSprite(actors.at(i)->getSprite())->y = actors.at(i)->getPos().y;
		//std::cout << "Sprite " << actors.at(i).getSprite() << " is at (" << frame->getSprite(actors.at(i).getSprite())->x << ", " << frame->getSprite(actors.at(i).getSprite())->y << std::endl;
		//std::cout << "Actor " << i << " is at (" << actors.at(i).getPos().x << ", " << actors.at(i).getPos().y << std::endl;
	}
}

void Core::init() {
	//Actor* player = new Actor(200, 200, 0);
	actors.emplace_back(new Actor(200, 200, 0));
	int player = actors.size() - 1;

	int* pixels = new int[100 * 100];
	for (int i = 0; i < 100 * 100; i++) {
		pixels[i] = 0x2222ff;
	}
	int playerTexture = frame->createTexture(pixels, 100, 100);
	int playerSprite = frame->createSprite(playerTexture, actors.at(player)->getPos().x, actors.at(player)->getPos().y);
	sprites.emplace_back(playerSprite);
	actors.at(player)->setSprite(playerSprite);
	
	std::function<void()> tick = std::bind(&Core::update, *this);
	frame->addRunFunc(tick);

	registerControls(player);
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


void Core::registerControls(int player)
{
	//std::cout << actors.at(player).getPos().x << " " << actors.at(player).getPos().y << " " << actors.at(player).getPos().z << " " << std::endl;
	controlled.emplace_back(player);
}
