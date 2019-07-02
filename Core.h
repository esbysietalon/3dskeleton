#pragma once
#include "Skeleton.h"
#include "Actor.h"

class Core {
public:
	Core(Skeleton* s);
	~Core();
	
	void update();
	void registerControls(int aci);

	void left();
	void up();
	void right();
	void down();
	void nleft();
	void nup();
	void nright();
	void ndown();
private:
	Skeleton* frame;

	void init();

	std::vector<int> sprites;
	std::vector<Actor*> actors;
	std::vector<int> controlled;


	
};