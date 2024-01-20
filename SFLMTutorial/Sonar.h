#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


#include "Grid.h"
#include "FillLine.h"
#include "ObstacleLine.h"

using namespace sf;

class Sonar
{
private:

	RenderWindow* window;
	Event event; 
	VideoMode videoMode;

	/* ======= Mouse Positions ======= */
	Vector2i mousePositionWindow;
	Vector2f mousePositionView; //float


	/* ======= Sonar Objects ======= */
	Grid base_grid;
	FillLine line;
	ObstacleLine obstacle_line;


	/* ======= Textures ======= */
	Font font;
	Text text;



	/* ======= Initializing Functions ======= */
	void initializeVariables();
	void initializeWindow();
	void initializeBaseplate();
	void initializeFont();
	void initializeText();

public:

	/* ======= Con Decon  ======= */
	Sonar();
	virtual ~Sonar();
	/* ========================== */


	/* ======= Acessors ======= */
	bool isWindowOpen();
	/* ======================== */


	/* ======= Functions ======= */
	void updateEvents();
	void update();
	void render();
	
};

