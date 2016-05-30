#include <math.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int ride( RenderWindow &window)
{


    //RenderWindow window(sf::VideoMode(640, 480), "Lesson 7. kychka-pc.ru");
    Image image;
    image.loadFromFile("machine.png");

    image.createMaskFromColor(Color (255, 255, 255));

    image.createMaskFromColor(Color (253, 253, 253));

    image.createMaskFromColor(Color (254, 254, 254));
    Texture herotexture;
    herotexture.loadFromImage(image);
    Sprite herosprite, tmpherosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 135, 72));
    herosprite.setPosition(250, 250);
    tmpherosprite = herosprite;
    float CurrentFrame = 0;//хранит текущий кадр
    Clock clock;
    float angle = 0;
    Vector2f vert;
    Vector2f pos;

    vert.x = 1;
    vert.y = 0;
    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            //if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
           // herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
            herosprite.move(0.1 * time * vert.x, 0.1 * time * vert.y);//происходит само движение персонажа вниз
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            //if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
           // herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
            herosprite.move(-0.1 * time * vert.x, -0.1 * time * vert.y);//происходит само движение персонажа вниз
        }
        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {

            angle += float(time)/1000;
            vert.x = cos(angle);
            vert.y = sin(angle);

        }
        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {

        angle -= float(time)/1000;
            vert.x = cos(angle);
            vert.y = sin(angle);
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape))
            break;

        pos = herosprite.getPosition();
        tmpherosprite.setPosition(int(-vert.x * 67.5 + 36 * vert.y + pos.x), int(-vert.y * 67.5 - 36 * vert.x + pos.y));
        tmpherosprite.setRotation(angle * 180 / 3.14);
        window.clear(Color(255, 255, 255));
        window.draw(tmpherosprite);
        window.display();
    }
}
