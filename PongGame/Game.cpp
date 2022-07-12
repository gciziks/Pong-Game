#include "Game.h"

// Initializers

void Game::initVariables()
{
	this->window = nullptr;
	//Game Variables (DEBUG only)
	this->ballXDirection = 1;
	this->ballYDirection = 1;
	this->multiplier = 60.f;
	this->playerStartPos = 50;
	this->iaStartPos = 750;
	this->dirCD = false;
	// Game Variables (Players choice)
	this->playersSpeed = 10.f;
	this->ballSpeed = 5;
	this->scoreP1 = 0;
	this->scoreP2 = 0;
	
}

void Game::initWindow()
{
	this->videoMode.height = 800;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Pong");
	//this->window->setFramerateLimit(60);

}

void Game::initFPS()
{
	this->clock = sf::Clock::Clock();
	this->previousTime = clock.getElapsedTime();

	this->font.loadFromFile("./resources/pixelmix.ttf");
	this->fpsText.setCharacterSize(20);
	this->fpsText.setFont(this->font);
	this->fpsText.setString("-- FPS");
	this->fpsText.setPosition(this->videoMode.width / 2.25f, this->videoMode.height - 25);
}

void Game::initScore()
{
	this->textScoreP1.setCharacterSize(20);
	this->textScoreP1.setFont(this->font);
	this->textScoreP1.setString("0");
	this->textScoreP1.setPosition(50, 10);
	this->textScoreP2.setCharacterSize(20);
	this->textScoreP2.setFont(this->font);
	this->textScoreP2.setString("0");
	this->textScoreP2.setPosition(this->videoMode.width - 50, 10);
}

void Game::initArena()
{
	this->roofS.setSize(sf::Vector2f(this->videoMode.width, 2.f));
	this->roofS.setFillColor(sf::Color::Yellow);
	this->roofS.setPosition(sf::Vector2f(0, 0));

	this->downS.setSize(sf::Vector2f(this->videoMode.width, 2.f));
	this->downS.setFillColor(sf::Color::Yellow);
	this->downS.setPosition(sf::Vector2f(0, this->videoMode.height -1));

	this->leftS.setSize(sf::Vector2f(2.f, this->videoMode.height));
	this->leftS.setFillColor(sf::Color::Yellow);
	this->leftS.setPosition(sf::Vector2f(0, 0));

	this->rightS.setSize(sf::Vector2f(2.f, this->videoMode.height));
	this->rightS.setFillColor(sf::Color::Yellow);
	this->rightS.setPosition(sf::Vector2f(this->videoMode.width - 1, 0));
}

void Game::initPlayer1()
{
	this->playerChar1.setSize(sf::Vector2f(25.f, 100.f));
	this->playerChar1.setFillColor(sf::Color::Black);
	this->playerChar1.setOutlineColor(sf::Color::Blue);
	this->playerChar1.setOutlineThickness(2.f);
	this->playerChar1.setPosition(sf::Vector2f(this->playerStartPos,100.f));
	this->playerColPos = this->playerStartPos + (this->playerChar1.getSize().x / 2.f);
	

}

void Game::initIA()
{
	this->iaChar.setSize(sf::Vector2f(25.f, 100.f));
	this->iaChar.setFillColor(sf::Color::Black);
	this->iaChar.setOutlineColor(sf::Color::Green);
	this->iaChar.setOutlineThickness(2.f);
	this->iaChar.setPosition(sf::Vector2f(this->iaStartPos, 100.f));
	this->iaColPos = this->iaStartPos - (this->iaChar.getSize().x / 2.f);
}

void Game::initBall()
{
	this->ballChar.setRadius(7.5f);
	this->ballChar.setFillColor(sf::Color::Black);
	this->ballChar.setOutlineColor(sf::Color::White);
	this->ballChar.setOutlineThickness(2.f);
	this->ballChar.setPosition(sf::Vector2f(350.f, 100.f));

}



// Constructors | Destructors

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFPS();
	this->initArena();
	this->initScore();
	this->initPlayer1();
	this->initIA();
	this->initBall();
	
}

Game::~Game()
{
	delete this->window;
}


// Accessors

const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

// Functions

void Game::updateDt()
{
	this->dt = this->dtClock.restart().asSeconds();
	
}

void Game::changeDirection(bool X)
{

	if (X) {
		this->ballXDirection = this->ballXDirection * -1;
		this->ballChar.move(this->ballXDirection * 2, 0);
		
	}
	else {
		this->ballYDirection = this->ballYDirection * -1;
		this->ballChar.move(0,this->ballYDirection * 2);
	}	
}

void Game::checkCollision()
{
	if (this->ballChar.getGlobalBounds().intersects(this->playerChar1.getGlobalBounds()) ||
		this->ballChar.getGlobalBounds().intersects(this->iaChar.getGlobalBounds()) //&& (this->ballChar.getPosition().x == this->playerColPos || this->ballChar.getPosition().x == this->iaColPos)
		) {
		
		this->changeDirection(true);
		
		
		

	}
	else if (this->ballChar.getGlobalBounds().intersects(this->roofS.getGlobalBounds()) ||
		this->ballChar.getGlobalBounds().intersects(this->downS.getGlobalBounds())
		) {
		
		this->changeDirection(false);
		
	}
}

void Game::moveBall(){

	if (this->ballChar.getPosition().x > this->playerColPos -2 && this->ballChar.getPosition().x < this->iaColPos + 2) {
		this->checkCollision();
		this->ballChar.move(sf::Vector2f(this->ballXDirection * (this->ballSpeed / 2) * this->dt * this->multiplier, this->ballYDirection * this->ballSpeed * this->dt * this->multiplier));
	}
	else {
		this->countPoint();
	}
}
void Game::countPoint()
{
	if (this->ballChar.getPosition().x <= this->playerColPos - 2) {
		this->scoreP2 += 1;
		this->textScoreP2.setString(std::to_string(this->scoreP2));
	}
	else if (this->ballChar.getPosition().x >= this->iaColPos + 2) {
		this->scoreP1 += 1;
		this->textScoreP1.setString(std::to_string(this->scoreP1));
		
	}
	this->ballChar.setPosition(this->videoMode.width / 2, this->videoMode.height / 2);
	this->changeDirection(true);
}

void Game::moveIA()
{
}


void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if(this->ev.key.code == sf::Keyboard::Escape) {
					this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::Z) {
				this->ballSpeed += 1;
			}
			if (this->ev.key.code == sf::Keyboard::X) {
				if (this->ballSpeed > 1) {
					this->ballSpeed -= 1;
				}
				
			}
		}
		
	}
}

void Game::renderArena()
{
	this->window->draw(this->roofS);
	this->window->draw(this->leftS);
	this->window->draw(this->rightS);
	this->window->draw(this->downS);
	this->window->draw(this->textScoreP1);
	this->window->draw(this->textScoreP2);
}

void Game::renderPlayers()
{
	this->window->draw(this->playerChar1);
	this->window->draw(this->iaChar);
}

void Game::renderBall()
{
	this->window->draw(this->ballChar);
}

void Game::fpsHandler()
{
	// Calculate FPS
	this->currentTime = this->clock.getElapsedTime();
	this->fps = 1.0f / (this->currentTime.asSeconds() - this->previousTime.asSeconds());
	this->fpsText.setString(std::to_string(int(floor(this->fps))) + " FPS");
	this->previousTime = this->currentTime;
}

void Game::inputHandler()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (this->playerChar1.getPosition().y > 0) {
			this->playerChar1.move(0.f, -this->playersSpeed * this->dt * this->multiplier);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (this->playerChar1.getPosition().y < this->videoMode.height - this->playerChar1.getSize().y) {
			this->playerChar1.move(0.f, this->playersSpeed * this->dt * this->multiplier);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (this->iaChar.getPosition().y > 0) {
			this->iaChar.move(0.f, -this->playersSpeed * this->dt * this->multiplier);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (this->iaChar.getPosition().y < this->videoMode.height - this->playerChar1.getSize().y) {
			this->iaChar.move(0.f, this->playersSpeed * this->dt * this->multiplier);
		}
	}

}








// Main Functions

void Game::update()
{
	
	this->updateDt();
	this->fpsHandler();

	this->inputHandler();
	this->moveBall();
	this->pollEvents();
}

void Game::render()
{
	// Clear last frame
	this->window->clear(sf::Color::Black);
	// Draw
	this->window->draw(this->fpsText); // FPS on screen
	this->renderArena();
	this->renderPlayers(); // Players on screen
	this->renderBall(); // Ball on screen
	// Display Screen
	this->window->display();
	//std::cout << "CD:" << this->cooldownCurrent << std::endl;

}
