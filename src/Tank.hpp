#ifndef TANK_H
#define TANK_H
#pragma once

#include "Bullet.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <math.h>

#define PI 3.14159265

class Tank
{
private:
	sf::ConvexShape base;
	sf::ConvexShape cannon;

	float tankPosX;
	float tankPosY;
	float tankRotation;
	float tankScale;
	float tankSpeed;

	bool is_rotating_clockwise;
	bool is_rotating_counter_clockwise;

	//bullets
	std::vector<Bullet> bullets;

public:
	Tank();
	~Tank();
	float getRotation();
	void initTank(float tankPosX, float tankPosY, float tankRotation, float tankScale, float tankSpeed);
	void update(bool go_forward, bool go_back, bool rotate_clockwise, bool rotate_counter_clockwise, float tankScale, float tankSpeed);
	void render(sf::RenderTarget& target);
	void spanwBullet();
	void updateBullets();
	void renderBullets(sf::RenderTarget& target);
};
#endif