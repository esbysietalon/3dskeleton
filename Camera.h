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
	void updateMousePosition(int x, int y);
	void setRotation(float theta, float phi);
	void setFov(float fov, float vfov);
	void move(move_t id);
private:
	float fov, vfov;
	float theta = 0;
	float phi = 0;
	int x, y, z;
	int focalX, focalY, focalZ;
	float hang_step, vang_step;
	int viewWidth, viewHeight;
	int mousex, mousey;
	int* pixels;
	int getCamDist(pos point);
	bool inView(pos point);
	bool withinFov(pos point);
	pos flatten(pos point);
};