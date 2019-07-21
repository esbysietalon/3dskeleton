#include "stdafx.h"
#include "Camera.h"
#include <iostream>

Camera::Camera(int width, int height)
{
	viewWidth = width;
	viewHeight = height;
	//pixels = new int[viewWidth * viewHeight];
}

Camera::~Camera()
{

}

void Camera::move(move_t id) {
	switch (id) {
	case move_t::LEFT:
		theta-=0.01;
		break;
	case move_t::RIGHT:
		theta+=0.01;
		break;
	case move_t::FRONT:
		z++;
		break;
	case move_t::BACK:
		z--;
		break;
	case move_t::UP:
		y--;
		break;
	case move_t::DOWN:
		y++;
		break;
	}
}
int Camera::getCamDist(pos xyz) {
	return (xyz.x - x) * (xyz.x - x) + (xyz.y - y) * (xyz.y - y) + (xyz.z - z) * (xyz.z - z);
}

float Camera::getAng(pos xyz, char fov_type) {
	switch (fov_type) {
	case 't':
		return atan2(xyz.z - z, xyz.x - x);
	case 'p':
		return atan2(xyz.y - y, xyz.z - z);
	default:
		return 0;
	}
	
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

bool Camera::inView(Actor* actor) {
	int sqdist = getCamDist(actor->getPos());
	if (sqdist == 0)
		return false;

	float xzang = getAng(actor->getPos(), 't');
	float yzang = getAng(actor->getPos(), 'p');
	
	float visAng = sqrt(max(actor->getDim())) / sqrt(sqdist);
	return (abs(xzang - theta) - visAng / 2 < fov) && (abs(yzang - phi) - visAng / 2 < vfov);
}

void Camera::generateView(std::vector<Actor*> actors, int* pixels)
{
	for(int i = 0; i < viewWidth * viewHeight; i++){
		pixels[i] = 0;
	}
	for (int i = 0; i < actors.size(); i++) {
		pos aPos = actors.at(i)->getPos();
		pos aDim = actors.at(i)->getDim();
		/*float xzang = getAng(actors.at(i)->getPos(), 't');
		float yzang = getAng(actors.at(i)->getPos(), 'p');
		std::cout << "xzang: " << xzang << " yzang: " << yzang << std::endl;*/
		//std::cout << aPos.x << " " << aPos.y << " " << aPos.z << std::endl;
		if (!inView(actors.at(i))) {
			//std::cout << "not in view" << std::endl;
			continue;
		}
		//std::cout << "in view" << std::endl;
		float dist = sqrt(getCamDist(aPos));
		float baseCamX = cos(theta) * dist;
		float baseCamY = cos(phi) * dist;
		//std::cout << "vang_step: " << vang_step << " hang_step: " << hang_step << std::endl;
		int llim_x = baseCamX + -1 * cos(-fov / 2) * dist;
		int rlim_x = baseCamX + cos(fov / 2) * dist;
		int ulim_y = baseCamY + sin(-vfov / 2) * dist;
		int dlim_y = baseCamY + sin(vfov / 2) * dist;
		//std::cout << "llim_x: " << llim_x << " rlim_x: " << rlim_x << " ulim_y: " << ulim_y << " dlim_y: " << dlim_y << std::endl;
		for (float yrayAng = -vfov / 2; yrayAng < vfov / 2; yrayAng += vang_step) {
			int corrected_y = baseCamY + sin(yrayAng) * dist;
			//std::cout << "yrayAng: " << yrayAng << " sin: " << sin(yrayAng) << " corrected_y: " << corrected_y <<  std::endl;
			for (float xrayAng = -fov / 2; xrayAng < fov / 2; xrayAng += hang_step) {
				//std::cout << "xrayAng: " << xrayAng << std::endl;
				int corrected_x = baseCamX + cos(xrayAng) * dist;
				
				//std::cout << "corrected_x: " << corrected_x << " corrected_y: " << corrected_y << std::endl;
				//std::cout << "left: " << aPos.x << " right: " << aPos.x + aDim.x << " up: " << aPos.y << " down: " << aPos.y + aDim.y << std::endl;
				if (corrected_x >= aPos.x && corrected_x < aPos.x + aDim.x) {
					//std::cout << "in x view" << std::endl;
					if (corrected_y >= aPos.y && corrected_y < aPos.y + aDim.y) {
						//std::cout << "corrected_x: " << corrected_x << " corrected_y: " << corrected_y << " in view" << std::endl;
						//std::cout << (int)(corrected_x - aPos.x) + (int)(corrected_y - aPos.y) * aDim.x << " - " << actors.at(i)->getPixels()[(int)(corrected_x - aPos.x) + (int)(corrected_y - aPos.y) * aDim.x] <<  std::endl;
						//std::cout << (int)(xrayAng / fov) + (int)(yrayAng / vfov) * viewWidth << std::endl;
						int screenX = ((xrayAng + fov / 2) / fov) * viewWidth;
						int screenY = ((yrayAng + vfov / 2) / vfov) * viewHeight;
						
						//std::cout << "screenX: " << screenX << " screenY: " << screenY << std::endl;
						pixels[screenX + screenY * viewWidth] = 0xffffff;//actors.at(i)->getPixels()[(int)(corrected_x - aPos.x) + (int)(corrected_y - aPos.y) * aDim.x];
					}
					else {
						//std::cout << "corrected_x: " << corrected_x << " corrected_y: " << corrected_y << " not in view" << std::endl;
					}
				}
				else {
					//std::cout << "corrected_x: " << corrected_x << " corrected_y: " << corrected_y << " not in view" << std::endl;
				}
				
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
	this->theta = theta;
	this->phi = phi;
}

void Camera::setFov(float fov, float vfov)
{
	this->fov = fov;
	this->vfov = vfov;
	hang_step = fov / viewWidth;
	vang_step = vfov / viewHeight;
}
