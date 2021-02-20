#include "Tank.hpp"

Tank::Tank()
{
}

Tank::~Tank()
{
}

float Tank::getRotation()
{
	return this->tankRotation;
}

void Tank::initTank(float tankPosX, float tankPosY, float tankRotation, float tankScale, float tankSpeed)
{
	//base
	this->base.setPointCount(12);
	this->base.setPoint(0, sf::Vector2f(0, 0));
	this->base.setPoint(1, sf::Vector2f(0, 2));
	this->base.setPoint(2, sf::Vector2f(2, 2));
	this->base.setPoint(3, sf::Vector2f(2, 9));
	this->base.setPoint(4, sf::Vector2f(0, 9));
	this->base.setPoint(5, sf::Vector2f(0, 11));
	this->base.setPoint(6, sf::Vector2f(16, 11));
	this->base.setPoint(7, sf::Vector2f(16, 9));
	this->base.setPoint(8, sf::Vector2f(14, 9));
	this->base.setPoint(9, sf::Vector2f(14, 2));
	this->base.setPoint(10, sf::Vector2f(16, 2));
	this->base.setPoint(11, sf::Vector2f(16, 0));
	this->base.setFillColor(sf::Color::Red);
	//this->base.setOutlineThickness(1);

	//cannon
	this->cannon.setPointCount(6);

	this->cannon.setPoint(0, sf::Vector2f(7, 0));
	this->cannon.setPoint(1, sf::Vector2f(7, 7));
	this->cannon.setPoint(2, sf::Vector2f(12, 4));
	this->cannon.setPoint(3, sf::Vector2f(20, 4));
	this->cannon.setPoint(4, sf::Vector2f(20, 3));
	this->cannon.setPoint(5, sf::Vector2f(12, 3));
	this->cannon.setFillColor(sf::Color::Blue);
	//this->cannon.setOutlineThickness(1);

	this->tankPosX = tankPosX;
	this->tankPosY = tankPosY;
	this->tankRotation = tankRotation;
	this->tankScale = tankScale;
	this->tankSpeed = tankSpeed;

	this->is_rotating_clockwise = false;
	this->is_rotating_counter_clockwise = false;
}

void Tank::update(bool go_forward, bool go_back, bool rotate_clockwise, bool rotate_counter_clockwise, float tankScale, float tankSpeed)
{
	//update variables
	this->tankScale = tankScale;
	this->tankSpeed = tankSpeed;

	//update pos and rotation based on input and context
	if (go_forward == true)
	{
		if (this->tankRotation == 0)
		{
			this->tankPosX += (this->tankSpeed / 60);
		}
		if (this->tankRotation == 90)
		{
			this->tankPosY -= (this->tankSpeed / 60);
		}
		if (this->tankRotation == 180)
		{
			this->tankPosX -= (this->tankSpeed / 60);
		}
		if (this->tankRotation == 270)
		{
			this->tankPosY += (this->tankSpeed / 60);
		}
		if (this->tankRotation > 270 && this->tankRotation < 360)
		{
			this->tankPosX += (this->tankSpeed / 60) * cos((360 - this->tankRotation) * PI / 180.0);
			this->tankPosY -= (this->tankSpeed / 60) * sin((360 - this->tankRotation) * PI / 180.0);
		}
		if (this->tankRotation > 180 && this->tankRotation < 270)
		{
			this->tankPosX -= (this->tankSpeed / 60) * cos((this->tankRotation - 180) * PI / 180.0);
			this->tankPosY -= (this->tankSpeed / 60) * sin((this->tankRotation - 180) * PI / 180.0);
		}
		if (this->tankRotation > 90 && this->tankRotation < 180)
		{
			this->tankPosX -= (this->tankSpeed / 60) * cos((this->tankRotation - 90) * PI / 180.0);
			this->tankPosY += (this->tankSpeed / 60) * sin((this->tankRotation - 90) * PI / 180.0);
		}
		if (this->tankRotation > 0 && this->tankRotation < 90)
		{
			this->tankPosX += (this->tankSpeed / 60) * cos(this->tankRotation * PI / 180.0);
			this->tankPosY += (this->tankSpeed / 60) * sin(this->tankRotation * PI / 180.0);
		}
	}

	if (go_back == true)
	{
		this->tankPosX -= (this->tankSpeed / 60);
	}
	// rotate clockwise
	if (rotate_clockwise == true)
	{
		if (this->is_rotating_clockwise == false)
		{
			//first time rotate
			this->is_rotating_clockwise = true;
		}
		else
		{
			// already doing rotation
		}
	}
	//update clockwise rotation
	if (this->is_rotating_clockwise)
	{
		this->tankRotation += 1;
		if (fmod(this->tankRotation, 15.f) == 0)
		{
			// end of rotation
			this->is_rotating_clockwise = false;
		}
	}
	// rotate counter clockwise
	if (rotate_counter_clockwise == true)
	{
		if (this->is_rotating_counter_clockwise == false)
		{
			//first time rotate
			this->is_rotating_counter_clockwise = true;
		}
		else
		{
			// already doing rotation
		}
	}
	//update rotation
	if (this->is_rotating_counter_clockwise)
	{
		if (this->tankRotation >= 1)
		{
			this->tankRotation -= 1;
		}
		else
		{
			this->tankRotation = 360;
			this->tankRotation = 359;
		}
		if (fmod(this->tankRotation, 15.f) == 0)
		{
			// end of rotation
			this->is_rotating_counter_clockwise = false;
		}
	}

	this->tankRotation = abs(fmod(this->tankRotation, 360.f));

	//update graphic objects
	sf::FloatRect frBase, frCannon;
	sf::Vector2f veBase, veCannon;

	frBase = this->base.getLocalBounds();
	this->base.setOrigin(8.f, 5.5f);
	this->base.setRotation(this->tankRotation);
	this->base.setScale(this->tankScale, this->tankScale);
	this->base.setPosition(sf::Vector2f(this->tankPosX, this->tankPosY));
	veBase = this->base.getOrigin();

	frCannon = this->cannon.getLocalBounds();
	this->cannon.setOrigin(6.5f, 3.5f);
	this->cannon.setRotation(this->tankRotation);
	this->cannon.setScale(this->tankScale, this->tankScale);
	this->cannon.setPosition(sf::Vector2f(this->tankPosX, this->tankPosY));
	veCannon = this->cannon.getOrigin();

	this->updateBullets();
}

void Tank::render(sf::RenderTarget& target)
{
	target.draw(this->base);
	target.draw(this->cannon);
	this->renderBullets(target);
}

void Tank::spanwBullet()
{
	Bullet mybullet;
	mybullet.initBullet(this->tankPosX, this->tankPosY, this->tankRotation, 1, 200);
	this->bullets.push_back(mybullet);
}

void Tank::updateBullets()
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].update();
	}
}

void Tank::renderBullets(sf::RenderTarget& target)
{
	for (int i = 0; i < this->bullets.size(); i++)
	{
		this->bullets[i].render(target);
	}
}
