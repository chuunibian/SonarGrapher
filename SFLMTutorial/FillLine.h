#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class FillLine
{
private:
	//nested class line which is just the shape of the line...
	class Line
	{
	public:
		Line();
		~Line();
		ConvexShape fillLine;
	private:
		void initializeVariables();
	};

	Line lines[180]; //array of 180 lines on stack no pointer to heap
	ConvexShape shape;
	int counter = 0;
	RectangleShape test;
	bool header_flag = false; //Switches when
	int scan_end = 1;
	int scan_header = 0;


	void initializeVariables();
	void updateSonarScan();


public:

	FillLine();
	FillLine(int degree, int distance);
	~FillLine();

	int getScanHeader();
	int getScanEnd();
	void render(RenderWindow& target);
	void update();


};

