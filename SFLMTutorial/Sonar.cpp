#include "Sonar.h"

void Sonar::initializeVariables()
{
	this->window = nullptr;

}

void Sonar::initializeWindow()
{
	videoMode.height = 550;
	videoMode.width = 1050;
	window = new RenderWindow(videoMode, "Sonar Scan", Style::Titlebar | Style::Close);
	window->setFramerateLimit(60);
}



void Sonar::initializeBaseplate()
{

}

void Sonar::initializeFont()
{
	if (!this->font.loadFromFile("Fonts/dosis-light.ttf")) {
		std::cout << "Failed To Load Font. \n";
	};
}

void Sonar::initializeText()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(Color::White);
	this->text.setString("Test");

}




//CONSTRUCTOR *** DECONSTRUCTOR
Sonar::Sonar() 
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeFont();
	this->initializeText();
}



Sonar::~Sonar()
{
	delete this->window;
}



bool Sonar::isWindowOpen()
{
	return this->window->isOpen();
}


void Sonar::updateEvents() //poll
{
	//polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->event.key.code == Keyboard::Escape) {
				this->window->close();
			}
			break;
		}
	}
}

void Sonar::update()
{
	this->updateEvents();
	if (line.getScanEnd() == 179 && obstacle_line.getState()) {
		this->obstacle_line.updateD();
		std::cout << "test \n";
	}
	else {
		this->line.update(); //upd radar scan motion
		this->obstacle_line.update(this->line.getScanHeader());
		if (line.getScanEnd() == 179) {
			obstacle_line.setState(true);
			obstacle_line.resetFullTrans();
		}
	}
}


void Sonar::render()
{ 
	this->window->clear();
	this->base_grid.render(*window);
	this->line.render(*window);
	this->obstacle_line.render(*window);
	this->window->display();
}




