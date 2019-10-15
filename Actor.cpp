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
void Actor::sortCW(frame f) {
	pos start = f.wf.at(0);
	pos center = pos();
	for (int i = 0; i < f.wf.size(); i++) {
		center = center + f.wf.at(i);
	}
	center = center / (float)f.wf.size();
	//std::cout << " center x : " << center.x << " center y : " << center.y << " start x : " << start.x << " start y : " << start.y << std::endl;
	float ang_sc = atan2((float)(start.y - center.y), (float)(start.x - center.x));
	if (ang_sc < 0) {
		ang_sc += 2 * PI;
	}
	//std::cout << ang_sc << std::endl;
	struct {
		pos center = pos();
		float startAng = 0;
		void construct(pos c, float s) {
			startAng = s;
			center = c;
		}
		bool operator()(pos a, pos b) const
		{
			//printf("a.x - center.x: %d a.y - center.y: %d b.x - center.x: %d b.y - center.y: %d\n", a.x - center.x, a.y - center.y, b.x - center.x, b.y - center.y);
			float ang_a_sc = atan2(a.y - center.y, a.x - center.x);
			float ang_b_sc = atan2(b.y - center.y, b.x - center.x);
			/*if (abs(ang_a_sc) < 0.001)
				ang_a_sc = 0;
			if (abs(ang_b_sc) < 0.001)
				ang_b_sc = 0;
			if (ang_a_sc < 0)
				ang_a_sc += 2 * PI;
			//if (ang_a_sc >= 2 * PI)
			//	ang_a_sc -= 2 * PI;
			if (ang_b_sc < 0)
				ang_b_sc += 2 * PI;
			//if (ang_b_sc >= 2 * PI)
			//	ang_b_sc -= 2 * PI;//*/
			//ang_a_sc -= startAng;
			//ang_b_sc -= startAng;
			//std::cout << " ang_a_sc: " << ang_a_sc * 180 / PI << " ang_b_sc: " << ang_b_sc * 180 / PI << std::endl;
			return (ang_a_sc > ang_b_sc);
		}
	} clockwise_comparator;
	clockwise_comparator.construct(center, ang_sc);
	
	std::sort(f.wf.begin(), f.wf.end(), clockwise_comparator);
	
	this->sortedFrame = new pos[f.wf.size()];
	for (int i = 0; i < f.wf.size(); i++) {
		this->sortedFrame[i] = f.wf.at(i);
		//printf("i: %d (%d, %d)\n", i, f.wf.at(i).x, f.wf.at(i).y);
	}
	
}

void Actor::addFramePoint(pos xy) {
	skeleton.wf.emplace_back(xy);
	sortCW(skeleton);
}

pos* Actor::getSortedFrame() {
	return this->sortedFrame;
}
