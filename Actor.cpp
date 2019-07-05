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
	if (front) {
		z++;
	}
	if (back) {
		z--;
	}
}

void Actor::setSprite(int index)
{
	sprite = index;
}

void Actor::setSprite(int * texture, int w, int h)
{
	this->w = w;
	this->h = h;
	pixels = new int[w * h];
	for (int i = 0; i < w * h; i++) {
		//std::cout << texture[i] << " " << std::endl;
		pixels[i] = texture[i];
	}
}

int Actor::getSprite()
{
	return sprite;
}

int * Actor::getPixels()
{
	return pixels;
}

pos Actor::getPos()
{
	return pos(x, y, z);
}

pos Actor::getDim()
{
	pos dim(w, h, 0);
	return dim;
}
