#include <SFML/Graphics.hpp>
#include "window.h"
#include "drive.h"
using namespace sf;


int main(){
    RenderWindow window( VideoMode(1366, 768), "Test!", Style::Fullscreen);

    initialize();
    puts("done");
    menu(window);

    Clock clock;

    while(window.isOpen())
    {
        window.clear(Color::Black);
        //ride(window);
        menu(window);
        window.display();

    }
    return 0;
}
