#include "stdafx.h"
#include "Camera.h"
#include <iostream>
#define FOCAL_DIST 2
Camera::Camera(int width, int height)
{
	viewWidth = width;
	viewHeight = height;
	//pixels = new int[viewWidth * viewHeight];
}

Camera::~Camera()
{

}

void Camera::move(move_t id) {
	switch (id) {
	case move_t::LEFT:
		theta -= PI/12;
		break;
	case move_t::RIGHT:
		theta += PI/12;
		break;
	case move_t::FRONT:
		z++;
		break;
	case move_t::BACK:
		z--;
		break;
	case move_t::UP:
		y--;
		break;
	case move_t::DOWN:
		y++;
		break;
	}
}
int Camera::getCamDist(pos xyz) {
	return (xyz.x - x) * (xyz.x - x) + (xyz.y - y) * (xyz.y - y) + (xyz.z - z) * (xyz.z - z);
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
	pos flatpoint = flatten(point);
	return ((flatpoint.x >= 0 && flatpoint.x < this->viewWidth) && (flatpoint.y >= 0 && flatpoint.y < this->viewHeight) && (this->z < point.z));
}

int getSign(float num) {
	if (num == 0)
		return 0;
	return abs(num) / num;
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
pos Camera::flatten(pos point) {	
	int a1 = point.x;
	int b1 = point.y;
	int c1 = point.z;
	
	
	int x1 = this->viewWidth;
	int y1 = this->viewHeight;
	int cx = this->x + this->viewWidth / 2;
	int cy = this->y + this->viewHeight / 2;

	int a2 = a1 + (cx - a1) * min(c1, c1 - this->z) / (double) (c1);
	int b2 = b1 + (cy - b1) * min(c1, c1 - this->z) / (double) (c1);

	//a2 = a1 + (cx - a1) / ((double) nozero(point.z - this->z));
	//b2 = b1 + (cx - b1) / ((double) nozero(point.z - this->z));

	return pos(a2, b2, 0);
}

void Camera::generateView(std::vector<Actor*> actors, int* pixels)
{
	for(int i = 0; i < viewWidth * viewHeight; i++){
		pixels[i] = 0;
	}
	for (int i = 0; i < actors.size(); i++) {
		pos aPos = actors.at(i)->getPos();
		frame aframe = actors.at(i)->getFrame();
		for (int j = 0; j < aframe.wf.size(); j++) {
			pos point = aframe.wf.at(j) + aPos;
			if (!inView(point)) {
				continue;
			}
			pos flatpoint = flatten(point);
			int index = flatpoint.x + flatpoint.y * viewWidth;
			
			if (index >= 0 && index < viewWidth * viewHeight) {
				pixels[index] = 0xFF0000;
			}
				
		}
	}
}

void Camera::setPosition(int x, int y, int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Camera::setRotation(float theta, float phi)
{
	this->focalX = x - FOCAL_DIST * cos(theta);
	this->focalY = y - FOCAL_DIST * sin(phi);
	this->focalZ = z - FOCAL_DIST * sin(theta);
}

void Camera::setFov(float fov, float vfov)
{
	this->fov = fov;
	this->vfov = vfov;
	hang_step = fov / viewWidth;
	vang_step = vfov / viewHeight;
}
