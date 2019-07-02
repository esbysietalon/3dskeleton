#include "stdafx.h"
#include "Actor.h"
#include <iostream>

Actor::Actor() {
	x = 0;
	y = 0;
	z = 0;
}
Actor::Actor(int a, int b, int c) {
	x = a;
	y = b;
	z = c;
}
Actor::~Actor() {

}

void Actor::push(move_t index, bool act) {

	movevectors[index] = act;

}

void Actor::move()
{
	bool left = movevectors[LEFT];
	bool right = movevectors[RIGHT];
	bool up = movevectors[UP];
	bool down = movevectors[DOWN];
	bool front = movevectors[FRONT];
	bool back = movevectors[BACK];

	//std::cout << "moving ";

	if (left) {
		x--;
	}
	if (right) {
		x++;
	}
	if (up) {
		y--;
	}
	if (down) {
		y++;
	}
}

void Actor::setSprite(int index)
{
	sprite = index;
}

int Actor::getSprite()
{
	return sprite;
}

pos Actor::getPos()
{
	return pos(x, y, z);
}
