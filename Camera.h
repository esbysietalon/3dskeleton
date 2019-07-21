#pragma once
#include "Actor.h"
#include <math.h>
#include <vector>
class Camera {
public:
	Camera(int width, int height);
	~Camera();
	void generateView(std::vector<Actor*> actors, int* pixels);
	void setPosition(int x, int y, int z);
	void setRotation(float theta, float phi);
	void setFov(float fov, float vfov);
	void move(move_t id);
private:
	float theta, phi, fov, vfov;
	int x, y, z;
	float hang_step, vang_step;
	int viewWidth, viewHeight;
	int* pixels;
	int getCamDist(pos point);
	float getAng(pos point, char fov_type);
	bool inView(Actor* actor);
};