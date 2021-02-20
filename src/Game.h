#ifndef GAME_H
#define GAME_H

#include "Ground.hpp"
#include "Tank.hpp"

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

/*
 Game class
*/

class Game
{
public:
	Game();
	virtual ~Game();

	void pollEvents();
	void updateText();

	void update();
	void render();
	void updateTank();
	void renderGround(sf::RenderTarget& target);
	void renderTank(sf::RenderTarget& target);
	void renderText(sf::RenderTarget& target);

	const bool running();

protected:
private:
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;

	// mouse pos
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	// resources
	sf::Font font;

	// text
	sf::Text uiText;

	// Game logic
	unsigned points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	// Game objects
	Ground ground;
	//sf::ConvexShape tank;
	Tank tank;
	float tankPosX;
	float tankPosY;
	float tankRotation;
	float tankScale;
	float tankSpeed;

	//tank input events
	bool go_forward;
	bool go_back;
	bool rotate_clockwise;
	bool rotate_counter_clockwise;

	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initGround();
	void initTank();
};

#endif // GAME_H
