#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

class Game
{
private:

	RenderWindow* window;
	Event event; 
	VideoMode videoMode;

	/* ======= Mouse Positions ======= */
	Vector2i mousePositionWindow;
	Vector2f mousePositionView; //float


	/* ======= Game Objects ======= */
	RectangleShape Enemy; 
	std::vector<RectangleShape> Enemies;


	/* ======= Game Logics ======= */
	unsigned int points;
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	unsigned int maxEnemies;
	bool mouseHeld;
	bool endGameFlag;
	/* =========================== */


	/* ======= Textures ======= */
	Font font;
	Text text;
	/* ======================== */



	/* ======= Initializing Functions ======= */
	void initializeVariables();
	void initializeWindow();
	void initializeEnemy();
	void initializeFont();
	void initializeText();

public:

	/* ======= Con Decon  ======= */
	Game();
	virtual ~Game();
	/* ========================== */


	/* ======= Acessors ======= */
	bool isWindowOpen();
	const bool getEndGameFlag();
	/* ======================== */


	/* ======= Functions ======= */
	void updateText();
	void updateEvents();
	void updateMousePosition();
	void spawnEnemies();
	void update();
	void updateEnemies();

	void render();
	void renderText(RenderTarget& target);
	void renderEnemies(RenderTarget& target);
	
};

