#ifndef BULLET_H
#define BULLET_H
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <math.h>

#define PI 3.14159265

class Bullet
{
private:
	float bulletPosX;
	float bulletPosY;
	float bulletRotation;
	float bulletScale;
	float bulletSpeed;

	sf::CircleShape base;

public:
	Bullet();
	~Bullet();
	void initBullet(float bulletPosX, float bulletPosY, float bulletRotation, float bulletScale, float bulletSpeed);
	void update();
	void render(sf::RenderTarget& target);
	float getPosX();
	float getPosY();
};
#endif