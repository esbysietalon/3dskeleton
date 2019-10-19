#include "stdafx.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height)
{
	viewWidth = width;
	viewHeight = height;
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
	this->mousex = x;
	this->mousey = y;
}
void Camera::move(move_t id) {
	switch (id) {
	case move_t::LEFT:
		x-=10;
		break;
	case move_t::RIGHT:
		x+=10;
		break;
	case move_t::UP:
		y-=10;
		break;
	case move_t::DOWN:
		y+=10;
		break;
	}
}

bool Camera::inView(pos point) {
	return (point.x >= 0 && point.y >= 0 && point.x < viewWidth && point.y < viewHeight);
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

pos findEdgeIndex(pos* f, int len, int vw, int type) {
	int edgeX = f[0].x;
	int edgeY = f[0].y;
	for (int i = 0; i < len; i++) {
		if ((edgeX - f[i].x) * type > 0) {
			edgeX = f[i].x;
		}
		if ((edgeY - f[i].y) * type > 0) {
			edgeY = f[i].y;
		}
	}
	return pos(edgeX, edgeY);
}
int isVertex(pos* f, int len, pos point) {
	for (int i = 0; i < len; i++) {
		if (point.x == f[i].x && point.y == f[i].y) {
			//printf("%d: (%d, %d) is (%d, %d)\n", i, point.x, point.y, f[i].x, f[i].y);
			return i;
		}
	}
	return -1;
}
int isLocalExtrema(pos* f, int len, int index) {
	/*int maxY = f[0].y;
	int minY = f[0].y;
	for (int i = 0; i < len; i++) {
		if (f[i].y < minY) {
			minY = f[i].y;
		}
		if (f[i].y > maxY) {
			maxY = f[i].y;
		}
	}
	return !(f[index].y > minY && f[index].y < maxY);*/
	int prev = index - 1;
	if (prev < 0)
		prev += len;
	int next = (index + 1) % len;
	if (f[index].y > f[prev].y && f[index].y > f[next].y)
		return 1;
	if (f[index].y < f[prev].y && f[index].y < f[next].y)
		return -1;
	return 0;
}
int lookAhead(int* pixels, int x, int y, int end, int vw, pos* vertices, int vertlen) {
	int edges = 0;
	bool newEdge = true;
	for (int ix = x + 1; ix <= end; ix++) {
		/**/
		if (pixels[ix + y * vw] < 0) {
			if (int v = isVertex(vertices, vertlen, pos(ix, y)) >= 0) {
				if (isLocalExtrema(vertices, vertlen, v))
					continue;
			}
			if (newEdge){
				edges++;
				newEdge = false;
			}
		}
		else {
			newEdge = true;
		}
	}
	return edges;
}
void Camera::colorinFrame(pos* f, int len, int* pixels) {
	//std::cout << "COLOR IN FRAME" << std::endl;
	
	
	for (int i = 0; i < len; i++) {
		int j = (i + 1 == len) ? 0 : i + 1;
		pos start = f[i];
		pos end = f[j];
		


		//std::cout << "i: " << i << " " << start.x << ", " << start.y << " | " << end.x << ", " << end.y << std::endl;

		int x1 = start.x, x2 = end.x, y1 = start.y, y2 = end.y;

		float x, y, dx, dy, step;
		int k;

		dx = (x2 - x1);
		dy = (y2 - y1);

		//printf("dx %f dy %f\n", dx, dy);

		if (dx != 0 && dy != 0) {
			if (abs(dx) >= abs(dy))
				step = abs(dx);
			else
				step = abs(dy);

			dx = dx / step;
			dy = dy / step;
		}
		else {
			if (dx == 0 && dy != 0) {
				step = abs(dy);
				dy = dy / abs(dy);
				dx = 0;
			}
			else if(dx != 0 && dy == 0){
				step = abs(dx);
				dx = dx / abs(dx);
				dy = 0;
			}
			else {
				continue;
			}
		}

		//std::cout << "dx: " << dx << " dy: " << dy << " x1: " << x1 << " y1: " << y1 << " x2: " << x2 << " y2: " << y2 << std::endl;

		x = x1;
		y = y1;

		k = 1;
		while (k <= step)
		{
			pixels[(int) x + (int) y * viewWidth] = -1;
			x = x + dx;
			y = y + dy;
			k = k + 1;
		}
	}


	//odd-even/scanline method
	pos initialPoint = findEdgeIndex(f, len, viewWidth, 1);
	pos endPoint = findEdgeIndex(f, len, viewWidth, -1);
	//bool brushOn = false;
	int prevEdges = 0;
	//printf("initialPoint is (%d, %d); endPoint is (%d, %d)\n", initialPoint.x, initialPoint.y, endPoint.x, endPoint.y);
	for (int y = initialPoint.y; y <= endPoint.y; y++) {
		//brushOn = false;
		prevEdges = 0;
		bool foundExtrema = false;
		for (int x = initialPoint.x; x <= endPoint.x; x++) {
			if (x + y * viewWidth >= viewWidth * viewHeight)
				continue;
			if (pixels[x + y * viewWidth] < 0) {
				int vertex = isVertex(f, len, pos(x, y));
				if (vertex >= 0) {
					if (isLocalExtrema(f, len, vertex) != 0) {
						//brushOn = false;
						foundExtrema = true;
						//prevEdges++;
					}
					if(!foundExtrema){
						if (x < viewWidth - 1 && pixels[(x + 1) + y * viewWidth] >= 0) {
							prevEdges++;
							//brushOn = !brushOn;
						}
					}
				}else {
					//if (!foundExtension)
					
					if (x < viewWidth - 1 && pixels[(x + 1) + y * viewWidth] >= 0)
						prevEdges++;
							//brushOn = !brushOn;
				}
				
				/*if (prevEdges % 2 == 1) {
					if(!lookAhead(pixels, x, y, endPoint.x, viewWidth))
						prevEdges--;
				}
				else {
					//if (lookAhead(pixels, x, y, endPoint.x, viewWidth))
					//	prevEdges++;
				}*/
				pixels[x + y * viewWidth] = 0x22FF22;
			}
			else {
				if (foundExtrema)
					foundExtrema = false;
				int forwardEdges = lookAhead(pixels, x, y, endPoint.x, viewWidth, f, len);
				if (forwardEdges > 0 && prevEdges > 0) {
					if (prevEdges % 2 == 1) {
						pixels[x + y * viewWidth] = 0xFF2222;
					}
					else {
						if (forwardEdges % 2 != 0)
							pixels[x + y * viewWidth] = 0xFF2222;
					}
				}
			}
			/*
			//printf("vertex %d\n", vertex);
			if (vertex >= 0) {
				//printf("%d %d isVertex\n", x, y);
				//if (f[(vertex + 1) % len].y == f[vertex].y) {
					//printf("flatline\n");
					//if (pixels[x + y * viewWidth] < 0) {
						//printf("0\n");
						//brushOn = !brushOn;
						//pixels[x + y * viewWidth] = 0x22FF22;
						//printf("x is %d and y is %d and brush is %d\n", x, y, brushOn);
					//}else if (brushOn) {
						//printf("1\n"); {
						//pixels[x + y * viewWidth] = 0x22FF22;
					//}
				//}
				//else {
					//printf("2\n");
					//if (pixels[x + y * viewWidth] < 0) {
						pixels[x + y * viewWidth] = 0x22FF22;
						brushOn = true;
						//brushOn = !brushOn;
					//}
						
					//brushOn = false;
				//}
			}
			else {
				//printf("isNotVertex");
				if (pixels[x + y * viewWidth] < 0) {
					//printf("3\n");
					brushOn = !brushOn;
					pixels[x + y * viewWidth] = 0x22FF22;
				}
				if (brushOn) {
					//printf("4\n");
					pixels[x + y * viewWidth] = 0x22FF22;
				}
				
			}*/
			/*if (isVertex(f, len, pos(x, y))) {
				//printf("isVertex");
				pixels[x + y * viewWidth] = 0x22FF22;
			}
			else {
				//printf("isNotVertex");
				if (pixels[x + y * viewWidth] == -1) {
					brushOn = !brushOn;
					pixels[x + y * viewWidth] = 0x22FF22;
				}
				if (brushOn) {
					pixels[x + y * viewWidth] = 0x22FF22;
				}
			}*/
		}
	}
}

void Camera::generateView(std::vector<Actor*> actors, int* pixels)
{
	for(int i = 0; i < viewWidth * viewHeight; i++){
		pixels[i] = 0;
	}
	for (int i = 0; i < actors.size(); i++) {
		pos aPos = actors.at(i)->getPos();
		frame aframe = actors.at(i)->getFrame();
		
		colorinFrame(actors.at(i)->getSortedFrame(), aframe.wf.size(), pixels);
	}
}

void Camera::setPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

