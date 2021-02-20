#ifndef GROUND_H
#define GROUND_H
#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

class Ground
{
private:
	//walls
	std::vector<sf::ConvexShape> walls;

public:
	Ground();
	~Ground();

	void initGround();
	void render(sf::RenderTarget& target);

};
#endif