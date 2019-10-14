#pragma once
#include "Actor.h"
#include <math.h>
#include <vector>
class Camera {
public:
	Camera(int width, int height);
	~Camera();
	void generateView(std::vector<Actor*> actors, int* pixels);
	void setPosition(int x, int y);
	void updateMousePosition(int x, int y);
	void move(move_t id);
private:
	int x, y;
	int viewWidth, viewHeight;
	int mousex, mousey;
	int* pixels;
	bool inView(pos point);
	void colorinFrame(frame f, int* pixels);
};