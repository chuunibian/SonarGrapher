#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Game mainGame;
    
    while (mainGame.isWindowOpen())
    {
        //Update, update the status logic
        mainGame.update();

        //Render, visualizing updates
        mainGame.render();

    }

    return 0;
}
