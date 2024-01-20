#include "Grid.h"

Vector2f spokeCalculate(float angle, float hypotenuse)
{
	float radians = angle/180.f * PI;
	//std::cout << radians << "\n";
	float xComp = cos(radians) * hypotenuse + 525; //because is cos 
	float yComp = 550 - sin(radians) * hypotenuse;
	std::cout << xComp << "   " << yComp << "\n";

	Vector2f coordinate(xComp, yComp);
	return coordinate;

}

void Grid::initializeFont()
{
	if (!font.loadFromFile("Fonts/Dosis-light.ttf")) {
		std::cout << "Font Error";
	}
	else {
		std::cout << "Success";
	}
}

//Issue for duplicate monitor it seems when dragged over it becomes scuffed
void Grid::initializeVariables()
{ //maybe array of cicrlce and increment that way no big lines like this
	center_point.x = 525;
	center_point.y = 850;

	half_circle1.setRadius(500.f);
	half_circle1.setPosition(25.f, 50.f);
	half_circle1.setPointCount(CIRCLE_PRECISION);
	half_circle1.setFillColor(Color::Black);
	half_circle1.setOutlineColor(Color::Green);
	half_circle1.setOutlineThickness(1.f); //Outline thickness

	half_circle2.setRadius(500.f - 125.f);
	half_circle2.setPosition(25.f + 125.f, 50.f + 125.f);
	half_circle2.setPointCount(CIRCLE_PRECISION);
	half_circle2.setFillColor(Color::Black);
	half_circle2.setOutlineColor(Color::Green);
	half_circle2.setOutlineThickness(1.f); //Outline thickness

	half_circle3.setRadius(500.f - 125.f - 125.f);
	half_circle3.setPosition(25.f + 125.f * 2, 50.f + 125.f * 2);
	half_circle3.setPointCount(CIRCLE_PRECISION);
	half_circle3.setFillColor(Color::Black);
	half_circle3.setOutlineColor(Color::Green);
	half_circle3.setOutlineThickness(1.f); //Outline thickness

	half_circle4.setRadius(500.f - 125.f - 125.f - 125.f);
	half_circle4.setPosition(25.f + 125.f * 3, 50.f + 125.f * 3);
	half_circle4.setPointCount(CIRCLE_PRECISION);
	half_circle4.setFillColor(Color::Black);
	half_circle4.setOutlineColor(Color::Green);
	half_circle4.setOutlineThickness(1.f); //Outline thickness

	guide_line = VertexArray(Lines, 14); //These are dec on stack
	for (int i = 0; i < 7; i++) {
		guide_line[i * 2].position = Vector2f(525, 550);
		guide_line[i * 2].color = Color::Green;
		guide_line[i * 2 + 1].position = spokeCalculate(i * 30, 535);
		guide_line[i * 2 + 1].color = Color::Green;
	}

	//Setting texts////////////////////////////
	//Based on i, 0 1 2 3 for edge X, 4 5 6 7 8 for spoke angles. No 180 or 0 indicator
	// for 0 1 2 3, the 3rd is back a bit so not in loop XXX NOT ANYMORE
	for (int i = 0; i < 4; i++) {
		texts[i].setFont(font);
		texts[i].setCharacterSize(20);
		texts[i].setFillColor(Color::Green);
		texts[i].setString(std::to_string((i+1) * (MAX_DISTANCE_SCAN / 4)) + "cm");
		texts[i].setPosition(Vector2f((525 + 65) + 125 * i, 550 - 25));
	}

	for (int i = 4; i < 9; i++) {
		texts[i].setFont(font);
		texts[i].setCharacterSize(20);
		texts[i].setFillColor(Color::Green);
		texts[i].setString(std::to_string((i - 3) * 30) + "°");
	}


	//Manual inputs for locations for brevi
	texts[4].setPosition(Vector2f(975, 300));
	texts[5].setPosition(Vector2f(790, 95));
	texts[6].setPosition(Vector2f(525 + 5, 20));
	texts[7].setPosition(Vector2f(45, 295));
	texts[8].setPosition(Vector2f(225, 95));
	//////////////////////////////////////////

}

Grid::Grid()
{
	initializeVariables();
	initializeFont();
}

Grid::~Grid()
{
}

void Grid::renderText(RenderTarget& target) {

	for (int i = 0; i < 9; i++) {
		target.draw(texts[i]);
	}

}
void Grid::render(RenderWindow& target)
{
	target.draw(half_circle1);
	target.draw(half_circle2);
	target.draw(half_circle3);
	target.draw(half_circle4);
	target.draw(guide_line);
	renderText(target);
}

void Grid::update()
{

}
