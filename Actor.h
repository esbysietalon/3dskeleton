#pragma once

#include <math.h>
#include <vector>
#define PI 3.14159
struct pos {
	int x, y;
	pos(int a, int b) {
		x = a;
		y = b;
	}
	pos operator+(const pos& a) const
	{
		return pos(a.x + x, a.y + y);
	}
};
struct frame {
	std::vector<pos> wf;
};
enum move_t { LEFT, RIGHT, UP, DOWN };

class Actor {
public:
	Actor();
	Actor(int x, int y);
	~Actor();

	void push(move_t index, bool act);
	
	void move();
	void setSprite(int index);
	void setSprite(int* pixels, int w, int h);

	frame getFrame();
	void addFramePoint(pos xy);

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