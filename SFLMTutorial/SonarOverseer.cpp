#include <SFML/Graphics.hpp>
#include "Sonar.h"

using namespace sf;

int main()
{
    srand(static_cast<unsigned>(time(NULL)));

    Sonar mainSonar;
    
    while (mainSonar.isWindowOpen())
    {
        //Update, update the status logic
        mainSonar.update();
        //Render, visualizing updates
        mainSonar.render();
    }

    return 0;
}
