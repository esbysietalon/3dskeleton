#pragma once

#include <math.h>
#include <vector>
#define PI 3.14159
struct pos {
	int x, y, z;
	pos(int a, int b, int c) {
		x = a;
		y = b;
		z = c;
	}
	pos operator+(const pos& a) const
	{
		return pos(a.x + x, a.y + y, a.z + z);
	}
};
struct frame {
	std::vector<pos> wf;
};
enum move_t { LEFT, RIGHT, UP, DOWN, FRONT, BACK, ROTL, ROTR, ROTU, ROTD };

class Actor {
public:
	Actor();
	Actor(int x, int y, int z);
	~Actor();

	void push(move_t index, bool act);
	
	void move();
	void setSprite(int index);
	void setSprite(int* pixels, int w, int h);

	frame getFrame();
	void addFramePoint(pos xyz);

	int getSprite();
	int* getPixels();

	pos getPos();
private:
	int sprite = -1;

	bool movevectors[6] = { false, false, false, false, false, false };

	int* pixels;

	int x = 0, y = 0, z = 0;
	double phi = 0;
	double theta = PI / 2;
	int speed = 1;
	
	frame skeleton;
};