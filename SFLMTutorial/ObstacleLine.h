#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace sf;
constexpr auto MAX_DISTANCE_REC = 500;
constexpr auto MAX_DISTANCE = 300;


class ObstacleLine
{
private:
	RectangleShape obstacle_lines[180];
	Vector2f rectangle_size;
	int full_trans;
	void initializeVariables();
	int calculateRatio(float distance);


public:
	ObstacleLine();
	~ObstacleLine();
	int getFullTrans();
	void resetFullTrans();
	void setState(bool set);
	bool getState();
	bool state; //defines the state of updating for the obstacles.
	void render(RenderWindow& target);
	void update(int header);
	void updateD();
};

