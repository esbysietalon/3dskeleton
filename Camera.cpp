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
int getSign(float num) {
	if (num == 0)
		return 0;
	return abs(num) / num;
}
void Camera::updateMousePosition(int x, int y) {
	
	double theta_n = this->theta + getSign(x - mousex) * (PI / 60) * (1 + 10 * abs(mousex - this->viewWidth / 2) / (this->viewWidth / 2));
	double phi_n = this->phi + getSign(y - mousey) * (PI / 60) * (1 + 10 * abs(mousex - this->viewWidth / 2) / (this->viewWidth / 2));
	
	this->mousex = x;
	this->mousey = y;
	
	theta_n = PI +  PI * sin((this->viewWidth / 2 - this->mousex) / (double) (this->viewWidth) * PI);
	phi_n = PI + PI * sin((this->viewHeight / 2 - this->mousey) / (double) (this->viewHeight) *  PI);
	
	this->theta = theta_n;
	this->phi = phi_n;

}
void Camera::move(move_t id) {
	switch (id) {
	case move_t::ROTU:
		phi += PI / 60;
		break;
	case move_t::ROTD:
		phi -= PI / 60;
		break;
	case move_t::ROTL:
		theta += PI / 60;
		break;
	case move_t::ROTR:
		theta -= PI / 60;
		break;
	case move_t::LEFT:
		x-=10;
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
		z-=10;
		break;
	case move_t::UP:
		y-=10;
		break;
	case move_t::DOWN:
		y+=10;
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
	if (flatpoint.z > 0)
		return false;
	//return true;
	return ((flatpoint.x >= 0 && flatpoint.x < this->viewWidth) && (flatpoint.y >= 0 && flatpoint.y < this->viewHeight));
}


bool Camera::withinFov(pos point) {
	int x = point.x;
	int y = point.y;
	int z = point.z;

	double theta_p = atan2(this->z - point.z, this->x - point.x);
	double phi_p = atan2(this->z - point.z, this->y - point.z);
	
	//std::cout << theta_p << " " << this->theta << " " << phi_p << " " << this->phi << std::endl;
	//std::cout << ((abs(theta_p + PI / 2 - (this->theta)) <= PI) && (abs(phi_p + PI / 2 - (this->phi)) <= PI)) << std::endl;
	return true;
	//return ((abs(theta_p - (this->theta - PI / 2)) <= PI / 2) && (abs(phi_p - (this->phi - PI / 2)) <= PI / 2));
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
	
	int at = a0 - this->x;
	int bt = b0 - this->y;
	int ct = c0 - this->z;


	float dist_theta = sqrt((at - this->x) * (at - this->x) + (ct - this->z) * (ct - this->z));
	double theta_o = atan2(ct - this->z, at - this->x);

	double theta_n = theta_o - this->theta;


	//std::cout << theta_n * 180 / PI << std::endl;
	double ar = at - at +  dist_theta * cos(theta_n);
	double br = bt;
	double cr = ct - ct +  dist_theta * sin(theta_n);

	float dist_phi = sqrt((bt - this->y) * (bt - this->y) + (ct - this->z) * (ct - this->z));
	double phi_o = atan2(ct - this->z, bt - this->y);

	double phi_n = phi_o - this->phi;

	double a1 = ar;
	double b1 = br - br + dist_phi * cos(phi_n);
	double c1 = cr - cr + dist_phi * sin(phi_n);


	if (!withinFov(pos(a1, b1, c1))) {
		return pos(0, 0, 1);
	}
	
	

	int x1 = this->viewWidth;
	int y1 = this->viewHeight;
	int cx = this->viewWidth / 2;
	int cy = this->viewHeight / 2;

	int a2 = a1 + (cx - a1) * max(1, min(c1, c1 - this->z)) / (double) (c1) * 0.95;
	int b2 = b1 + (cy - b1) * max(1, min(c1, c1 - this->z)) / (double) (c1) * 0.95;

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
				pixels[index] = 0xFFFFFF;
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
	
}

void Camera::setFov(float fov, float vfov)
{
	this->fov = fov;
	this->vfov = vfov;
	hang_step = fov / viewWidth;
	vang_step = vfov / viewHeight;
}
