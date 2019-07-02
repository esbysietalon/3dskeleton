#pragma once

#include <math.h>

#define PI 3.14159
struct pos {
	int x, y, z;
	pos(int a, int b, int c) {
		x = a;
		y = b;
		z = c;
	}
};
enum move_t { LEFT, RIGHT, UP, DOWN, FRONT, BACK };

class Actor {
public:
	Actor();
	Actor(int x, int y, int z);
	~Actor();

	void push(move_t index, bool act);
	
	void move();
	void setSprite(int index);
	int getSprite();

	pos getPos();
private:
	int sprite = -1;

	bool movevectors[6] = { false, false, false, false, false, false };

	int x = 0, y = 0, z = 0;
	double phi = 0;
	double theta = PI / 2;
	int speed = 1;
};