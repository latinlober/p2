#include "Game.h"

Game::Game(bool serverMode, bool clientMode, std::string remotePlayer, std::int16_t remotePort)
{
	//ctor
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initNetwork(serverMode, clientMode, remotePlayer, remotePort);
}

Game::~Game()
{
	//dtor
	delete this->window;
}

// functions

void Game::updateTank()
{
	//check if clicked upon

	// move enemies

	// check mouse input

	// update tank
	this->tank.update(this->go_forward,
		this->go_back,
		this->rotate_clockwise,
		this->rotate_counter_clockwise,
		this->tankScale,
		this->tankSpeed);
}

void Game::renderGround(sf::RenderTarget& target)
{
	// render ground
	this->ground.render(target);
}

void Game::renderTank(sf::RenderTarget& target)
{
	// render tank
	this->tank.render(target);
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->uiText);
}

void Game::update()
{

	this->pollEvents();

	//update mouse position

	//std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";

	this->updateText();

	this->updateTank();
}

void Game::render()
{
	//clear screen
	this->window->clear();

	//draw ground
	this->renderGround(*this->window);

	// render tank
	this->renderTank(*this->window);

	// draw text
	this->renderText(*this->window);

	// display
	this->window->display();
}

void Game::pollEvents()
{
	// Process events
	this->go_forward = false;
	this->go_back = false;
	this->rotate_clockwise = false;
	this->rotate_counter_clockwise = false;

	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
			// Close window : exit
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::Escape)
					this->window->close();
				if (this->ev.key.code == sf::Keyboard::Right)
					this->rotate_clockwise = true;
				if (this->ev.key.code == sf::Keyboard::Left)
					this->rotate_counter_clockwise = true;
				if (this->ev.key.code == sf::Keyboard::Up)
					this->go_forward = true;
				if (this->ev.key.code == sf::Keyboard::Down)
					this->go_back = true;
				if (this->ev.key.code == sf::Keyboard::O)
					this->tankScale += 1;
				if (this->ev.key.code == sf::Keyboard::L)
					this->tankScale -= 1;
				if (this->ev.key.code == sf::Keyboard::M)
					this->tankSpeed += 10;
				if (this->ev.key.code == sf::Keyboard::N)
					this->tankSpeed -= 10;
				if (this->ev.key.code == sf::Keyboard::Space)
					this->tank.spanwBullet();
				break;
		}
	}
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Points: " << this->points << "\n";
	ss << "Health: " << this->health << "\n";
	ss << "Speed: " << this->tankSpeed << "\n";
	ss << "Rotation: " << this->tank.getRotation() << "\n";
	this->uiText.setString(ss.str());
}

const bool Game::running()
{
	return this->window->isOpen();
}

void Game::initTank()
{

	// init tank
	this->tank.initTank(this->tankPosX, this->tankPosY, this->tankRotation, this->tankScale, this->tankSpeed);
}

void Game::initNetwork(bool serverMode, bool clientMode, std::string remotePlayer, std::int16_t remotePort)
{
	this->serverMode = serverMode;
	this->clientMode = clientMode;
	this->remotePlayer = remotePlayer;
	this->remotePort = remotePort;

	// bind the socket to a port
	if (socketServer.bind(6666) != sf::Socket::Done)
	{
		// error...
		std::cout << "Error openning local upd socket 6666. Review it !!!" << std::endl;
	}
	//waiting for peer
	if (serverMode)
	{
		char data[100];
		std::size_t received;
		sf::IpAddress sender;
		unsigned short port;
		if (socketServer.receive(data, 100, received, sender, port) != sf::Socket::Done)
		{
			// error...
			std::cout << "Error reciving data from " << sender << std::endl;
			exit(1);
		}
		std::cout << "Received " << received << " bytes from " << sender << " on port " << port << std::endl;
		this->remotePlayer = sender.toString();
		this->remotePort = 6666;
	}
	else
	{
		// initiate conn to server
		char data[100];
		sf::IpAddress recipient = this->remotePlayer;
		unsigned short port = this->remotePort;
		if (socketClient.send(data, 100, recipient, port) != sf::Socket::Done)
		{
			// error...
			std::cout << "Error sending data to " << recipient << std::endl;
			exit(1);
		}
		std::cout << "Sended message to " << recipient << " on port " << port << std::endl;
	}
}

void Game::initVariables()
{
	this->window = nullptr;
	// Game Logic
	this->points = 0;
	this->health = 10;

	//tank init
	this->tankPosX = 500.f;
	this->tankPosY = 500.f;
	this->tankRotation = 0.f;
	this->tankScale = 10.f;
	this->tankSpeed = 100;

	this->go_forward = false;
	this->go_back = false;
	this->rotate_clockwise = false;
	this->rotate_counter_clockwise = false;

	this->initGround();
	this->initTank();
}

void Game::initWindow()
{
	this->videomode.height = 1080;
	this->videomode.width = 1920;
	this->window = new sf::RenderWindow(this->videomode, "A tope tiu", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (this->font.loadFromFile("src/Fonts/maass-slicer/maass slicer Italic.ttf"))
	{
		std::cout << "ERROR::GAME::INIFONTS::Failed to load font!"
				  << "\n";
	}
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(28);
	this->uiText.setPosition(10.f, 10.f);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("init text");
}

void Game::initGround()
{
	this->ground.initGround();
}
