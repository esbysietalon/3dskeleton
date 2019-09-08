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
	case move_t::ROTL:
		theta -= PI / 60;
		break;
	case move_t::ROTR:
		theta += PI / 60;
		break;
	case move_t::LEFT:
		x-=5;
		//theta -= PI/12;
		break;
	case move_t::RIGHT:
		x+=10;
		//theta += PI/12;
		break;
	case move_t::FRONT:
		z+=10;
		break;
	case move_t::BACK:
		z-=100;
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
	if (flatpoint.z == 69)
		return false;
	//return true;
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
	int a0 = point.x;
	int b0 = point.y;
	int c0 = point.z;
	
	float dist = sqrt((point.x - this->x) * (point.x - this->x) + (point.y - this->y) * (point.y - this->y) + (point.z - this->z) * (point.z - this->z));
	double theta_o = atan2(point.z - this->z, point.x - this->x);

	double theta_n = theta_o+this->theta;
	
	//std::cout << theta_n * 180 / PI << std::endl;
	int ar = this->x + dist * cos(theta_n);
	int br = b0;
	int cr = this->z + dist * sin(theta_n);

	if (cr < this->z) {
		return pos(0, 0, 69);
	}
	
	int a1 = ar + this->x;
	int b1 = br + this->y;
	int c1 = cr + this->z;

	if (c1 < this->z) {
		return pos(0, 0, 69);
	}

	int x1 = this->viewWidth;
	int y1 = this->viewHeight;
	int cx = this->viewWidth / 2;
	int cy = this->viewHeight / 2;

	int a2 = a1 + (cx - a1) * min(c1, c1 - this->z) / (double) (c1) * 0.75;
	int b2 = b1 + (cy - b1) * min(c1, c1 - this->z) / (double) (c1) * 0.75;

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
