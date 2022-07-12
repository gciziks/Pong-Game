#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

class Game
{
	private:
		// Window Variables
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		//Handles FPS
		sf::Font font;
		sf::Text fpsText;
		sf::Clock clock;
		sf::Time previousTime;
		sf::Time currentTime;
		float fps;

		// DeltaTime
		sf::Clock dtClock;
		float dt;
		float multiplier;

		// Players Variables
		sf::RectangleShape playerChar1;
		sf::RectangleShape iaChar;
		float playersSpeed;
		float playerStartPos, playerColPos;
		float iaStartPos, iaColPos;

		//Ball Variables
		sf::CircleShape ballChar;	
		float ballSpeed;
		int ballXDirection;
		int ballYDirection;
		bool dirCD;
		float cooldownMax, cooldownCurrent;
		
		// Arena Variables
		sf::RectangleShape roofS, leftS, rightS, downS;	
		sf::Text textScoreP1;
		sf::Text textScoreP2;
		int scoreP1;
		int scoreP2;


		// Main Initializers
		void initVariables();
		void initWindow();
		void initFPS();

		// Initializers
		void initScore();
		void initArena();
		void initPlayer1();
		void initIA();
		void initBall();
	public:

		//Constructors | Desctructors
		Game();
		virtual ~Game();

		//Accessors
		const bool getWindowIsOpen() const;

		// Functions
		void updateDt();
		void changeDirection(bool X);
		void checkCollision();
		void moveBall();
		void countPoint();
		void moveIA();
		void pollEvents();
		void renderArena();
		void renderPlayers();
		void renderBall();
		void fpsHandler();
		void inputHandler();


		// Main Functions
		void update();
		void render();
};

