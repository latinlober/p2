#include "Bullet.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::initBullet(float bulletPosX, float bulletPosY, float bulletRotation, float bulletScale, float bulletSpeed)
{
	this->bulletPosX = bulletPosX;
	this->bulletPosY = bulletPosY;
	this->bulletRotation = bulletRotation;
	this->bulletScale = bulletScale;
	this->bulletSpeed = bulletSpeed;

	this->base.setRadius(5);
	this->base.setOrigin(2.5f, 2.5f);
	this->base.setPosition(this->bulletPosX, this->bulletPosY);
	this->base.setFillColor(sf::Color::White);
}

void Bullet::update()
{

	if (this->bulletRotation == 0)
	{
		this->bulletPosX += (this->bulletSpeed / 60);
	}
	if (this->bulletRotation == 90)
	{
		this->bulletPosY += (this->bulletSpeed / 60);
	}
	if (this->bulletRotation == 180)
	{
		this->bulletPosX -= (this->bulletSpeed / 60);
	}
	if (this->bulletRotation == 270)
	{
		this->bulletPosY -= (this->bulletSpeed / 60);
	}
	if (this->bulletRotation > 270 && this->bulletRotation < 360)
	{
		this->bulletPosX += (this->bulletSpeed / 60) * cos((this->bulletRotation) * PI / 180.0);
		this->bulletPosY += (this->bulletSpeed / 60) * sin((this->bulletRotation) * PI / 180.0);
		//		this->bulletPosX += (this->bulletSpeed / 60) * cos((360 - this->bulletRotation) * PI / 180.0);
		//		this->bulletPosY -= (this->bulletSpeed / 60) * sin((360 - this->bulletRotation) * PI / 180.0);
	}
	if (this->bulletRotation > 180 && this->bulletRotation < 270)
	{
		this->bulletPosX += (this->bulletSpeed / 60) * cos((this->bulletRotation) * PI / 180.0);
		this->bulletPosY += (this->bulletSpeed / 60) * sin((this->bulletRotation) * PI / 180.0);
	}
	if (this->bulletRotation > 90 && this->bulletRotation < 180)
	{
		this->bulletPosX += (this->bulletSpeed / 60) * cos((this->bulletRotation) * PI / 180.0);
		this->bulletPosY += (this->bulletSpeed / 60) * sin((this->bulletRotation) * PI / 180.0);
	}
	if (this->bulletRotation > 0 && this->bulletRotation < 90)
	{
		this->bulletPosX += (this->bulletSpeed / 60) * cos(this->bulletRotation * PI / 180.0);
		this->bulletPosY += (this->bulletSpeed / 60) * sin(this->bulletRotation * PI / 180.0);
	}

	this->base.setPosition(sf::Vector2f(this->bulletPosX, this->bulletPosY));

	std::cout << "Bullet: " << this->bulletPosX << ":" << this->bulletPosY << "\n";
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->base);
}

float Bullet::getPosX()
{
	return this->bulletPosX;
}

float Bullet::getPosY()
{
	return this->bulletPosY;
}