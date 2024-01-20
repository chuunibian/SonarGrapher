#include "FillLine.h"
#include <iostream>


void FillLine::initializeVariables()
{
	//Set static rotation
	for (int i = 0; i < 180;  i++) {
		lines[i].fillLine.setRotation(i-90); //from my orientation of line you would need 0 to 90 and then 270 to 360 as angles
	}
}

void FillLine::updateSonarScan()
{
	if (scan_header > 180) {
		scan_header = 0;
		scan_end = 1;
	}
	else
	{
		if (scan_header < 65) //make constexpr 65
		{
			for (int i = 0; i < scan_header; i++) {
				lines[i].fillLine.setFillColor(Color(0, 255, 0, i * 4)); //the 4 is based off 256 / 64
			}
			scan_header += 1;
		}
		else {
			if (scan_header >= 180 && scan_end < 180) { //attempt to clear right tail area
				int temp = 0;
				for (int j = scan_end + 1; j < scan_header + 1; j++, temp++) {
					lines[j].fillLine.setFillColor(Color(0, 255, 0, temp * 4));
				}
				lines[scan_end - 1].fillLine.setFillColor(Color(0, 255, 0, 0));
				scan_end += 1;
			}
			else
				{
				int temp = 0;
				for (int j = scan_end + 1; j < scan_header + 1; j++, temp++) {
					lines[j].fillLine.setFillColor(Color(0, 255, 0, temp * 4));
				}
				lines[scan_end - 1].fillLine.setFillColor(Color(0, 255, 0, 0));
				scan_end += 1;
				scan_header += 1;
			}
		}
	}
}

FillLine::FillLine()
{
	initializeVariables();
}

FillLine::FillLine(int degree, int distance)
{
}


FillLine::~FillLine()
{
}

int FillLine::getScanHeader()
{
	return scan_header;
}

int FillLine::getScanEnd()
{
	return scan_end;
}

void FillLine::render(RenderWindow& target)
{
	for (int i = 0; i < 180; i++) {
		target.draw(lines[i].fillLine);
	}
	target.draw(test);
}

void FillLine::update()
{
	updateSonarScan();
}

FillLine::Line::~Line()
{
}

void FillLine::Line::initializeVariables()
{
	fillLine.setPointCount(8);
	fillLine.setPoint(0, Vector2f(0, 5));
	fillLine.setPoint(1, Vector2f(2.25, 0));
	fillLine.setPoint(2, Vector2f(6.25, 0)); //thickness change in x here of shape is ~8? maybe make constanet!!!
	fillLine.setPoint(3, Vector2f(8.5, 5));
	fillLine.setPoint(4, Vector2f(8.5, 505.f));
	fillLine.setPoint(5, Vector2f(6.25, 510.f));
	fillLine.setPoint(6, Vector2f(2.25, 510.f));
	fillLine.setPoint(7, Vector2f(0, 505));
	fillLine.setOrigin(Vector2f(0.f, 510.f));
	fillLine.setPosition(Vector2f(525, 550));
	fillLine.setFillColor(Color(0, 255, 0, 0)); //looping use this as the thing!}
}

FillLine::Line::Line()
{
	initializeVariables();
}
