#pragma once

#include <math.h>
#include <vector>
#include <algorithm>
#include <functional>
#define PI 3.14159
struct pos {
	int x, y;
	pos() {
		x = 0;
		y = 0;
	}
	pos(int a, int b) {
		x = a;
		y = b;
	}
	pos operator+(const pos& a) const
	{
		return pos(a.x + x, a.y + y);
	}
	pos operator/(const float a) const
	{
		return pos(x / a, y / a);
	}
};
struct frame {
	std::vector<pos> wf;
	frame operator+(const frame& a) const {
		frame nf = frame();
		for (int i = 0; i < wf.size(); i++) {
			pos np = wf.at(i);
			if (i < a.wf.size()) {
				np = np + a.wf.at(i);
			}
			nf.wf.emplace_back(np);
		}
		return nf;
	}
	frame operator+(const pos& a) const {
		frame nf = frame();
		for (int i = 0; i < wf.size(); i++) {
			pos np = wf.at(i) + a;
			nf.wf.emplace_back(np);
		}
		return nf;
	}
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
	void sortCW(frame f);
	pos* getSortedFrame();
private:
	int sprite = -1;

	bool movevectors[6] = { false, false, false, false, false, false };

	int* pixels;

	int x = 0, y = 0, z = 0;
	double phi = 0;
	double theta = PI / 2;
	int speed = 1;
	
	pos* sortedFrame = nullptr;
	frame skeleton;
};