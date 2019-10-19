#pragma once
#include "Skeleton.h"
#include "Actor.h"
#include "Camera.h"
#include <random>


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

	double rand();
private:
	Skeleton* frame;
	Camera* camera;

	void init();

	std::vector<int> sprites;
	std::vector<Actor*> actors;
	std::vector<int> controlled;

	std::mt19937* rng;

	int* pixels;
	int sw, sh;

	int screen, screenTexture;

	
};