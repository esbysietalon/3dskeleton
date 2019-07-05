#include "stdafx.h"
#include "Camera.h"

Camera::Camera(int width, int height)
{
	viewWidth = width;
	viewHeight = height;
	//pixels = new int[viewWidth * viewHeight];
}

Camera::~Camera()
{

}



void Camera::generateView(std::vector<Actor*> actors, int* pixels)
{
	for(int i = 0; i < viewWidth * viewHeight; i++){
		pixels[i] = 0;
	}
	for (int i = 0; i < actors.size(); i++) {
		pos aPos = actors.at(i)->getPos();
		//int dist = getCamDist(aPos);

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
	this->theta = theta;
	this->phi = phi;
}

void Camera::setFov(float fov, float vfov)
{
	this->fov = fov;
	this->vfov = vfov;
}
