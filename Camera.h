#pragma once
#include "Actor.h"
#include <math.h>
class Camera {
public:
	Camera(int width, int height);
	~Camera();
	int* generateView(Actor* actors);
	void setPosition(int x, int y, int z);
	void setRotation(float theta, float phi);
	void setFov(float fov, float vfov);
private:
	float theta, phi, fov, vfov;
	int x, y, z;
	int viewWidth, viewHeight;
};