#include "stdafx.h"
#include "Actor.h"
#include <iostream>

Actor::Actor() {
	x = 0;
	y = 0;
}
Actor::Actor(int a, int b) {
	x = a;
	y = b;
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

void Actor::setSprite(int * texture, int w, int h)
{
	pixels = new int[w * h];
	for (int i = 0; i < w * h; i++) {
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
	return pos(x, y);
}

frame Actor::getFrame() {
	return skeleton;
}
void Actor::addFramePoint(pos xy) {
	skeleton.wf.emplace_back(xy);
}
