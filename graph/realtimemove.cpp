#include <math.h>
#include "drive.h"
#include "window.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

using namespace sf;
int realTimeMove(RenderWindow &window)
{
    window.close();
    Clock clock, clock1;

    bool flag = true;
    while (!Keyboard::isKeyPressed(Keyboard::Space))
    {
        char ch = 1;
        clock.restart();
        if (Keyboard::isKeyPressed(Keyboard::W)) {
            if (flag)
            {
                clock1.restart();
                flag = false;
            }
            ch *= 2;
        }
        else if (!flag)
        {
            std::cout<<'\n'<<clock1.getElapsedTime().asMicroseconds()<<std::endl;
            flag = true;
        }
        if (Keyboard::isKeyPressed(Keyboard::S)) {
            ch *= 3;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)) {
            ch *= 5;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)) {
            ch *= 7;
        }
        if (ch % 7 == 0 && ch % 5 == 0)
            ch /= 35;
        if (ch % 2 == 0 && ch % 3 == 0)
            ch /= 6;
        if (ch % 10 == 0)
        {
            ch = 'j';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 65090);
        }
        else if (ch % 14 == 0)
        {
            ch = 'k';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 56600);
        }
        else if (ch % 15 == 0 )
        {
            ch = 'h';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 84500);
        }
        else if (ch % 21 == 0)
        {
            ch = 'g';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 93000);
        }
        else if (ch % 2 == 0)
        {
            ch = 'w';
            move_send(ch);

            while (clock.getElapsedTime().asMicroseconds() < 28000);
        }
        else if (ch % 3 == 0)
        {
            ch = 's';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 75000);
        }
        else if (ch % 5 == 0)
        {
            ch = 'd';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 112000);
        }
        else if (ch % 7 == 0)
        {
            ch = 'a';
            move_send(ch);
            while (clock.getElapsedTime().asMicroseconds() < 103000);
        }
        else if(Keyboard::isKeyPressed(Keyboard::Escape))
        {
            RenderWindow window( VideoMode(1300, 700), "Test!");
            menu(window);
        }
    }
    //menu(window);
}
