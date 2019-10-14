#pragma once
#include "Skeleton.h"
#include "Actor.h"
#include "Camera.h"

class Core {
public:
	Core(Skeleton* s);
	~Core();
	
	void update();
	void registerControls(int aci);

	void updateMousePosition();
	
	void left();
	void up();
	void right();
	void down();
private:
	Skeleton* frame;
	Camera* camera;

	void init();

	std::vector<int> sprites;
	std::vector<Actor*> actors;
	std::vector<int> controlled;

	int* pixels;
	int sw, sh;

	int screen, screenTexture;

	
};