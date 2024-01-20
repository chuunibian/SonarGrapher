#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>


constexpr auto NUMBER_OF_SPOKES = 14;
constexpr auto PI = 3.141592653589793238;
constexpr auto XY_OFFSET = 25.0;
constexpr auto CIRCLE_PRECISION = 100;
constexpr auto MAX_DISTANCE_SCAN = 300;


using namespace sf;

class Grid
{
private:
	CircleShape half_circle1;
	CircleShape half_circle2;
	CircleShape half_circle3;
	CircleShape half_circle4;

	VertexArray guide_line;
	Vector2f center_point;

	Font font;
	Text texts[9];

	void initializeVariables();
	void initializeFont();
	void renderText(RenderTarget& target);


public:
	Grid();
	~Grid();

	void render(RenderWindow& target);
	void update();
};

