#include "Game.h"

void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 50.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 20;
	this->mouseHeld = false;
	this->endGameFlag = false;

}

void Game::initializeWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new RenderWindow(this->videoMode, "Testing", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}



void Game::initializeEnemy()
{
	this->Enemy.setPosition(0.f,0.f);
	this->Enemy.setSize(Vector2f(50.f, 50.f));
	//this->Enemy.setScale(Vector2f(0.5f, 0.5f));
	this->Enemy.setFillColor(Color::Cyan);
	//this->Enemy.setOutlineColor(Color::Green);
	//this->Enemy.setOutlineThickness(20.f);
}

void Game::initializeFont()
{
	if (!this->font.loadFromFile("Fonts/dosis-light.ttf")) {
		std::cout << "Failed To Load Font. \n";
	};
}

void Game::initializeText()
{
	this->text.setFont(this->font);
	this->text.setCharacterSize(30);
	this->text.setFillColor(Color::White);
	this->text.setString("Test");

}




//CONSTRUCTOR *** DECONSTRUCTOR
Game::Game() 
{
	this->initializeVariables();
	this->initializeWindow();
	this->initializeFont();
	this->initializeText();
	this->initializeEnemy();
}



Game::~Game()
{
	delete this->window;
}



bool Game::isWindowOpen()
{
	return this->window->isOpen();
}

const bool Game::getEndGameFlag()
{
	return this->endGameFlag;
}



void Game::updateText()
{
	std::stringstream ss;
	ss << "Points: " << this->points << "\n" << "Health: " << this->health << "\n";
	this->text.setString(ss.str());
	//this->text.setString("Points: " + std::to_string(this->points) + "\n" + "Health: " + std::to_string(this->health) + "\n");
}

void Game::updateEvents() //poll
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



void Game::updateMousePosition()
{
	this->mousePositionWindow = Mouse::getPosition(*this->window);
	this->mousePositionView = this->window->mapPixelToCoords(this->mousePositionWindow);
}



void Game::spawnEnemies()
{
	this->Enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->Enemy.getSize().x)),0.f); // minus enemy size to prevent OOB spawn

	int type = rand() % 5;

	switch (type)
	{
	case 0:
		this->Enemy.setScale(Vector2f(0.2f, 0.2f));
		this->Enemy.setFillColor(Color::Blue);
		break;
	case 1:
		this->Enemy.setScale(Vector2f(0.3f, 0.3f));
		this->Enemy.setFillColor(Color::Yellow);
		break;
	case 2:
		this->Enemy.setScale(Vector2f(0.4f, 0.4f));
		this->Enemy.setFillColor(Color::Green);
		break;
	case 3:
		this->Enemy.setScale(Vector2f(0.5f, 0.5f));
		this->Enemy.setFillColor(Color::White);
		break;
	case 4:
		this->Enemy.setScale(Vector2f(0.6f, 0.6f));
		this->Enemy.setFillColor(Color::Magenta);
		break;
	default:
		this->Enemy.setScale(Vector2f(0.9f, 0.9f));
		this->Enemy.setFillColor(Color::Transparent);
		break;
	}

	//Spawn enemy pushes it to vector for tracking and usage
	this->Enemies.push_back(this->Enemy);
}


void Game::updateEnemies()
{
	/* ======= Enemy Timer spawn updates ======= */
	if (this->Enemies.size() < this->maxEnemies) 
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			this->spawnEnemies();
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}
	/* ========================================= */


	/* ======= Moving Enemies and Update Y axis Check ======= */
	for (int i = 0; i < this->Enemies.size(); i++) {

		this->Enemies[i].move(0.f, 1.f);

		//if beyond y axis
		if (this->Enemies[i].getPosition().y > this->window->getSize().y) {
			this->Enemies.erase(this->Enemies.begin() + i);
			//decrement health
			this->health -= 1;
		}
	}
	/* ====================================================== */


	/* ======= Attack Or Click Updates ======= */
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		bool deletedFlag = false;
		if (this->mouseHeld == false) { //next iteration will not be false if held
			this->mouseHeld = true;
			for (auto i = 0; i < this->Enemies.size() && deletedFlag == false; i++) { //check which enemy was clicked then delete
				if (this->Enemies[i].getGlobalBounds().contains(this->mousePositionView)) {

					if (this->Enemies[i].getFillColor() == Color::Blue) {
						this->points += 10;
					}
					else if (this->Enemies[i].getFillColor() == Color::Yellow) {
						this->points += 8;
					}
					else if (this->Enemies[i].getFillColor() == Color::Green) {
						this->points += 6;
					}
					else if (this->Enemies[i].getFillColor() == Color::White){
						this->points += 4;
					}
					else if (this->Enemies[i].getFillColor() == Color::Magenta) {
						this->points += 2;
					}

					//Delete enemy
					deletedFlag = true;
					this->Enemies.erase(this->Enemies.begin() + i);
				}
			}
		}	
	}
	else {
		this->mouseHeld = false;
	}
	/* ====================================== */

}

void Game::update()
{
	this->updateEvents();

	if (this->endGameFlag == false) {

		this->updateMousePosition(); //important to 

		this->updateText();

		this->updateEnemies();
	}

	if (this->health <= 0) {
		this->endGameFlag = true;
	}
}

void Game::renderEnemies(RenderTarget& target)
{
	for (auto& i : this->Enemies)
	{
		target.draw(i);
	}
}

void Game::render()
{ //order is important

	this->window->clear();
	this->renderEnemies(*this->window);
	this->renderText(*this->window);
	this->window->display();
}

void Game::renderText(RenderTarget& target)
{
	target.draw(this->text);
}



