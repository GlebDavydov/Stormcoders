#include <math.h>
#include "drive.h"
#include "window.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>

#define PI 3.141593

using namespace sf;
int realTimeMove(RenderWindow &window)
{
    //window.close();
    move_send('0'); //Accel initialize
    Image image;
    image.loadFromFile("arrow.png");
    image.createMaskFromColor(Color(255, 255, 255));
    Texture herotexture;
    herotexture.loadFromImage(image);
    Sprite herosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 48, 33));
    herosprite.setPosition(250, 250);
    herosprite.setOrigin(0, 17);
    image.create(1270, 720, Color::White);
    Texture texture;
    Sprite sprite;
    sprite.setTexture(texture);
    Event event;
    Vector2f vect(1, 0);
    float speed = 0.1, ax = 0, ay = 0, angle = 0;
    Clock clock;
    int distance = 0;
    int distFlag = 0;
    while (window.isOpen())
    {

        char buff[100];
        move_send('l');
        distance = atoi(ReadCOM(buff));
        printf("\nDistance: %d", distance);
        if(distance < 30){
            distFlag++;
        }
        else if(distFlag > 0)
            distFlag--;
        if(distFlag >= 3){
            //MessageWindow("Obstacle Detected!");
            window.close();
            return 0;
        }
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

        image.setPixel(herosprite.getPosition().x, herosprite.getPosition().y, Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 1270, 720));
        /*if (Keyboard::isKeyPressed(Keyboard::W))
            ax = 20.0f;
        else if (Keyboard::isKeyPressed(Keyboard::S))
            ax = -20.0f;
        else
            ax = 0.0f;
        if (Keyboard::isKeyPressed(Keyboard::A))
            ay = -100.0f;
        else if (Keyboard::isKeyPressed(Keyboard::D))
            ay = 100.0f;
        else
            ay = 0.0f;*/
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
        //move_send('p');
        //ReadCOM(buff);
        //ax = atof(buff);
        //move_send('q');
        //ReadCOM(buff);
        //ay = atof(buff);
        //speed += ax * time / 10000;
        //angle += time * ay / speed / 100000;
        vect.x = cos(angle);
        vect.y = sin(angle);
        herosprite.move(speed * vect.x, speed * vect.y);
        herosprite.setRotation(angle * 180 / PI);
        window.clear(Color::White);
        window.draw(sprite);
        window.draw(herosprite);
        window.display();

        }
    }
    return 0;

    //menu(window);
}
