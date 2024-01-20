#include "ObstacleLine.h"

void ObstacleLine::initializeVariables()
{
	//For this reading format is angle first line then distance second line ~360 total lines
	//Lines are consecutive
	int counter = 0;
	std::ifstream fileInput("Misc/serialOutput.txt");
	std::string angle = "";
	std::string distance= "";
	while (counter < 180) {
		std::getline(fileInput, angle);
		std::getline(fileInput, distance);
		int int_angle = stoi(angle);
		int int_distance = stoi(distance);
		if (int_distance > MAX_DISTANCE) {
			rectangle_size = Vector2f(8.5, 500);
			obstacle_lines[counter].setOrigin(4.25, -500); //rotating around negative angle
			obstacle_lines[counter].setRotation(counter + 90);
			obstacle_lines[counter].setPosition(525, 550); //positon is static for all
			obstacle_lines[counter].setSize(rectangle_size);
			obstacle_lines[counter].setFillColor(Color(0, 0, 255, 0)); //set invisible BLUE as identifier of no show segment			 
		}
		else {
			rectangle_size = Vector2f(8.5, MAX_DISTANCE_REC - calculateRatio(int_distance));
			obstacle_lines[counter].setOrigin(4.25, -(calculateRatio(int_distance))); //rotating around negative angle
			obstacle_lines[counter].setRotation(counter + 90);
			obstacle_lines[counter].setPosition(525, 550); //positon is static for all
			obstacle_lines[counter].setSize(rectangle_size);
			obstacle_lines[counter].setFillColor(Color(255, 0, 0, 0)); //Initally set all red and 0s Alpha
		}
		counter += 1;
	}
	fileInput.close();
	full_trans = 0;
	state = false;
}

int ObstacleLine::calculateRatio(float distance)
{
	return distance / MAX_DISTANCE * MAX_DISTANCE_REC;
}

ObstacleLine::ObstacleLine()
{
	initializeVariables();
}

ObstacleLine::~ObstacleLine()
{
}

int ObstacleLine::getFullTrans()
{
	return full_trans;
}

void ObstacleLine::resetFullTrans()
{
	full_trans = 0;
}

void ObstacleLine::setState(bool set)
{
	state = set;
}

bool ObstacleLine::getState()
{
	return state;
}

void ObstacleLine::render(RenderWindow& target)
{
	for (int i = 0; i < 180; i++) {
		target.draw(obstacle_lines[i]);
	}
}

void ObstacleLine::update(int header)
{
	std::cout << " OLine update \n";
	for (int i = 0; i < 180; i++) {
		if (header < 179) { //HERE IS THE PROBLEM THE HEADER IS SOME VAL AND IT RESETS THE THING AT THE START BC HEADER IS header > i
			if (header > i && !obstacle_lines[i].getFillColor().b) {
				obstacle_lines[i].setFillColor(Color(255, 0, 0, 255));
			}
		}
	}
}

void ObstacleLine::updateD()
{
	if (full_trans > 254) {
		state = false;
		std::cout << "Setted!";
	}
	else {
		std::cout << "Else actived";
		full_trans += 5; //delay for dissapearnce of the obstacles
		for (int i = 0; i < 180; i++) {
			if (obstacle_lines[i].getFillColor().a) {
				obstacle_lines[i].setFillColor(Color(255, 0, 0, 255 - full_trans));
			}
		}
	}
}
