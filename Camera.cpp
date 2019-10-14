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
		//theta -= PI/12;
		break;
	case move_t::RIGHT:
		x+=10;
		//theta += PI/12;
		break;
	case move_t::UP:
		y-=10;
		break;
	case move_t::DOWN:
		y+=10;
		break;
	}
}

int max(pos abc) {
	if (abc.x > abc.y) {
		if (abc.x > abc.z) {
			return abc.x;
		}
		else {
			return abc.z;
		}
	}
	else {
		if (abc.y > abc.z) {
			return abc.y;
		}
		else {
			return abc.z;
		}
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
	for (int i = 0; i < viewWidth; i++) {
		for (int j = 0; j < viewHeight; j++) {
			pixels[i + j * viewWidth] = 0x00FF00;
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

void Camera::setPosition(int x, int y, int z)
{
	this->x = x;
	this->y = y;
}

