#include "stdafx.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height)
{
	viewWidth = width;
	viewHeight = height;
}

Camera::~Camera()
{

}
int getSign(float num) {
	if (num == 0)
		return 0;
	return abs(num) / num;
}
void Camera::updateMousePosition(int x, int y) {
	this->mousex = x;
	this->mousey = y;
}
void Camera::move(move_t id) {
	switch (id) {
	case move_t::LEFT:
		x-=10;
		break;
	case move_t::RIGHT:
		x+=10;
		break;
	case move_t::UP:
		y-=10;
		break;
	case move_t::DOWN:
		y+=10;
		break;
	}
}

bool Camera::inView(pos point) {
	return (point.x >= 0 && point.y >= 0 && point.x < viewWidth && point.y < viewHeight);
}

float max(float a, float b) {
	return (a > b) ? a : b;
}
float min(float a, float b) {
	return (a < b) ? a : b;
}
float nozero(float a) {
	return (a == 0) ? 1 : a;
}


void Camera::colorinFrame(frame f, int* pixels) {
	//std::cout << "COLOR IN FRAME" << std::endl;
	for (int i = 0; i < f.wf.size(); i++) {
		int j = (i + 1 == f.wf.size()) ? 0 : i + 1;
		pos start = f.wf.at(i);
		pos end = f.wf.at(j);
		
		//std::cout << "i: " << i << " " << start.x << ", " << start.y << " | " << end.x << ", " << end.y << std::endl;

		int x1 = start.x, x2 = end.x, y1 = start.y, y2 = end.y;

		float x, y, dx, dy, step;
		int k;

		dx = (x2 - x1);
		dy = (y2 - y1);

		if (dx != 0 && dy != 0) {
			if (abs(dx) >= abs(dy))
				step = dx;
			else
				step = dy;

			dx = dx / step;
			dy = dy / step;
		}
		else {
			if (dx == 0 && dy != 0) {
				step = abs(dy);
				dy = dy / abs(dy);
				dx = 0;
			}
			else if(dx != 0 && dy == 0){
				step = abs(dx);
				dx = dx / abs(dx);
				dy = 0;
			}
			else {
				continue;
			}
		}

		//std::cout << "dx: " << dx << " dy: " << dy << " x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << std::endl;

		x = x1;
		y = y1;

		k = 1;
		while (k <= step)
		{
			pixels[(int) x + (int) y * viewWidth] = 0x22FF22;
			x = x + dx;
			y = y + dy;
			k = k + 1;
		}
	}
}

void Camera::generateView(std::vector<Actor*> actors, int* pixels)
{
	for(int i = 0; i < viewWidth * viewHeight; i++){
		pixels[i] = 0;
	}
	for (int i = 0; i < actors.size(); i++) {
		pos aPos = actors.at(i)->getPos();
		frame aframe = actors.at(i)->getFrame();
		
		colorinFrame(aframe, pixels);
	}
}

void Camera::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

