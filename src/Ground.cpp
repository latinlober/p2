#include "Ground.hpp"

Ground::Ground()
{
}

Ground::~Ground()
{
}

void Ground::initGround()
{
	//base
	sf::ConvexShape base;
	base.setPointCount(4);
	base.setPoint(0, sf::Vector2f(0, 0));
	base.setPoint(1, sf::Vector2f(1920, 0));
	base.setPoint(2, sf::Vector2f(1920, 25));
	base.setPoint(3, sf::Vector2f(0, 25));
	base.setFillColor(sf::Color::Green);
	//base.setOutlineThickness(1);

	this->walls.push_back(base);

	base.setPointCount(4);
	base.setPoint(0, sf::Vector2f(0, 1080 - 25));
	base.setPoint(1, sf::Vector2f(1920, 1080 - 25));
	base.setPoint(2, sf::Vector2f(1920, 1080));
	base.setPoint(3, sf::Vector2f(0, 1080));
	base.setFillColor(sf::Color::Green);

	this->walls.push_back(base);

	base.setPointCount(4);
	base.setPoint(0, sf::Vector2f(1920 - 25, 0));
	base.setPoint(1, sf::Vector2f(1920 - 25, 1080));
	base.setPoint(2, sf::Vector2f(1920, 1080));
	base.setPoint(3, sf::Vector2f(1920, 0));
	base.setFillColor(sf::Color::Green);

	this->walls.push_back(base);

	base.setPointCount(4);
	base.setPoint(0, sf::Vector2f(0, 0));
	base.setPoint(1, sf::Vector2f(0, 1080));
	base.setPoint(2, sf::Vector2f(25, 1080));
	base.setPoint(3, sf::Vector2f(25, 0));
	base.setFillColor(sf::Color::Green);

	this->walls.push_back(base);
}

void Ground::render(sf::RenderTarget& target)
{
	for (int i = 0; i < this->walls.size(); i++)
	{
		target.draw(this->walls[i]);
	}
}