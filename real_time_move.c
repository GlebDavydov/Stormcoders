#include <math.h>
//#include "path.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
#define PI 3.1415

using namespace sf;
/*
float get_ax()
{
    return 1.0;
}

float get_ay()
{
    return 1.0;
}
*/
int main()
{
    RenderWindow window(VideoMode(1270, 720), "Justmve");
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
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();



        }

        image.setPixel(herosprite.getPosition().x, herosprite.getPosition().y, Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(IntRect(0, 0, 1270, 720));
        if (Keyboard::isKeyPressed(Keyboard::W))
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
            ay = 0.0f;
        speed += ax * time / 1000000;
        angle += time * ay / speed / 1000000;
        vect.x = cos(angle);
        vect.y = sin(angle);
        herosprite.move(speed * vect.x, speed * vect.y);
        herosprite.setRotation(angle * 180 / PI);
        window.clear(Color::White);
        window.draw(sprite);
        window.draw(herosprite);
        window.display();


    }
            return 0;
}

