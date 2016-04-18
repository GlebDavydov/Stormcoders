#include <math.h>
//#include <QTextStream>
//#include "path.h"
#include <SFML/Graphics.hpp>
#include <stdio.h>
void move_send(char ch)
{

}

struct move{
    float begin;
    float end;
    struct move * next;
};
struct moves{
    struct move * up;
    struct move * down;
    struct move * right;
    struct move * left;
};
using namespace sf;


struct moves * path()
{


    RenderWindow window(sf::VideoMode(640, 480), "Lesson 7. kychka-pc.ru");
    //RenderWindow window = *win;
    Image image;
    image.loadFromFile("images/arrow.png");
    image.createMaskFromColor(Color(255, 255, 255));
    Texture herotexture;
    herotexture.loadFromImage(image);
    Sprite herosprite, tmpherosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 48, 33));
    herosprite.setPosition(250, 250);
    herosprite.setOrigin(0, 17);
    tmpherosprite = herosprite;
    float CurrentFrame = 0;//хранит текущий кадр
    Clock clock, clock1;
    float angle = 0;
    float speed = 0;
    Vector2f vert;
    Vector2f pos;
    struct move move_up, move_down, move_left, move_right;
    struct move * tmpmove_up = NULL, * tmpmove_down = NULL, * tmpmove_left = NULL, * tmpmove_right = NULL;
    bool flag_up = false, flag_down = false, flag_left = false, flag_right = false;
    bool flag_up1 = false, flag_down1 = false, flag_left1 = false, flag_right1 = false;
    move_up.next = NULL;
    move_down.next = NULL;
    move_left.next = NULL;
    move_right.next = NULL;
    vert.x = 1;
    vert.y = 0;
    Image buffer;
    buffer.create(640, 480, Color::White);
    Texture bufferTexture;
    bufferTexture.loadFromImage(buffer);
    Sprite bufferSprite;
    bufferSprite.setTexture(bufferTexture);
    float start = clock1.getElapsedTime().asMicroseconds();
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
            if (!flag_up)
            {
                flag_up = true;
                struct move * tmp = new struct move;
                if (!flag_up1)
                {
                    tmpmove_up = &move_up;
                    flag_up1 = true;
                }
                tmpmove_up->next = tmp;
                tmpmove_up = tmp;
                tmpmove_up->next = NULL;
                tmpmove_up->begin = clock1.getElapsedTime().asMicroseconds() - start;
            }
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            speed += 0.0005 * time;
            //herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз
        }
        else
        {
            if (tmpmove_up != NULL && flag_up)
            tmpmove_up->end = clock1.getElapsedTime().asMicroseconds() - start;
            flag_up = false;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
            if (!flag_down)
            {
                flag_down = true;
                struct move * tmp = new struct move;
                if (!flag_down1)
                {
                    tmpmove_down = &move_down;
                    flag_down1 = true;
                }
                tmpmove_down->next = tmp;
                tmpmove_down = tmp;
                tmpmove_down->next = NULL;
                tmpmove_down->begin = clock1.getElapsedTime().asMicroseconds() - start;
            }
            CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
            speed -= 0.0005 * time;
            //происходит само движение персонажа вниз
        }
        else
        {
            if (tmpmove_down != NULL && flag_down)
            tmpmove_down->end = clock1.getElapsedTime().asMicroseconds() - start;
            flag_down = false;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
            if (!flag_right)
            {
                flag_right = true;
                struct move * tmp = new struct move;
                if (!flag_right1)
                {
                    tmpmove_right = &move_right;
                    flag_right1 = true;
                }
                tmpmove_right->next = tmp;
                tmpmove_right = tmp;
                tmpmove_right->next = NULL;
                tmpmove_right->begin = clock1.getElapsedTime().asMicroseconds() - start;
            }
            angle += time * speed / 200;
            vert.x = cos(angle);
            vert.y = sin(angle);
        }
        else
        {
            if (tmpmove_right != NULL && flag_right)
            tmpmove_right->end = clock1.getElapsedTime().asMicroseconds() - start;
            flag_right = false;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
            if (!flag_left)
            {
                flag_left = true;
                struct move * tmp = new struct move;
                if (!flag_left1)
                {
                    tmpmove_left = &move_left;
                    flag_left1 = true;
                }
                tmpmove_left->next = tmp;
                tmpmove_left = tmp;
                tmpmove_left->next = NULL;
                tmpmove_left->begin = clock1.getElapsedTime().asMicroseconds() - start;
            }
            angle -= time * speed / 200;
            vert.x = cos(angle);
            vert.y = sin(angle);
        }
        else
        {
            if (tmpmove_left != NULL && flag_left)
            tmpmove_left->end = clock1.getElapsedTime().asMicroseconds() - start;
            flag_left = false;
        }
        if ((Keyboard::isKeyPressed(Keyboard::Space))) {
            struct moves * mov = new struct moves;
            mov->up = &move_up;
            mov->left = &move_left;
            mov->right = &move_right;
            mov->down = &move_down;
            window.close();
            return mov;
        }
        if (speed > 1)
            speed = 1;
        if (speed < -1)
            speed = -1;
        if (!Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S))
        {
            if (speed < 0)
                speed += 0.0003 * time;
            if (speed > 0)
                speed -= 0.0003 * time;
        }
        herosprite.move(speed * vert.x, speed * vert.y);
        pos = herosprite.getPosition();
       // tmpherosprite.setPosition(int(16.5 * vert.y + pos.x), int( - 16.5 * vert.x + pos.y));
        herosprite.setRotation(angle * 180 / 3.14);

        if (pos.x > 1 && pos.y > 1 && pos.x < 639 && pos.y < 479)
        {
            buffer.setPixel(int(pos.x), int(pos.y), Color::Black);
            buffer.setPixel(int(pos.x + 1), int(pos.y), Color::Black);
            buffer.setPixel(int(pos.x - 1), int(pos.y), Color::Black);
            buffer.setPixel(int(pos.x), int(pos.y - 1), Color::Black);
            buffer.setPixel(int(pos.x), int(pos.y + 1), Color::Black);
            bufferTexture.loadFromImage(buffer);
            bufferSprite.setTexture(bufferTexture);
        }
        //while (clock.getElapsedTime().asMicroseconds() < 10000)

        window.clear(Color(255, 255, 255));
        window.draw(bufferSprite);
        window.draw(herosprite);

        window.display();
    }
    struct moves * mov = new struct moves;
    mov->up = &move_up;
    mov->left = &move_left;
    mov->right = &move_right;
    mov->down = &move_down;
    return mov;

}

int main()
{

   /* QTextStream cout(stdout);*/
    RenderWindow window(sf::VideoMode(640, 480), "Lesson 7. kychka-pc.ru");
    Image image;
    image.loadFromFile("images/machine.png");
    Texture herotexture;
    herotexture.loadFromImage(image);
    Sprite herosprite, tmpherosprite;
    herosprite.setTexture(herotexture);
    herosprite.setTextureRect(IntRect(0, 0, 135, 72));
    herosprite.setPosition(250, 250);
    herosprite.setOrigin(68, 36);
    Clock clock, clock1;
    float angle = 0;
    Vector2f vert;
    Vector2f pos;
    struct moves * mov = path();
    /*struct move * move_up = mov->up;
    struct move * move_down = mov->down;
    struct move * move_left = mov->left;
    struct move * move_right = mov->right;*/
    /*while (mov->up->next != NULL) {
        mov->up = mov->up->next;
        printf("%f %f\n", mov->up->begin, mov->up->end);
    }*/
    bool flag_up = mov->up->next == NULL;
    bool flag_down = mov->down->next == NULL;
    bool flag_left = mov->left->next == NULL;
    bool flag_right = mov->right->next == NULL;
    vert.x = 1;
    vert.y = 0;
    float speed = 0;
    mov->up = mov->up->next;
    mov->down = mov->down->next;
    mov->right = mov->right->next;
    mov->left = mov->left->next;
    bool is_mov_up = false, is_mov_down = false;
    float start = clock1.getElapsedTime().asMicroseconds();
    float time;
    clock.restart();
    Clock clock2;
    while (window.isOpen())
    {

        char ch = 1;
        clock2.restart();
        time = clock.getElapsedTime().asMicroseconds() / 800;
        clock.restart();
        is_mov_up = false;
        is_mov_down = false;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(!flag_up)
        if (clock1.getElapsedTime().asMicroseconds() - start > mov->up->begin) {
            if (clock1.getElapsedTime().asMicroseconds() - start > mov->up->end)
            {
                if (mov->up->next == NULL)
                    flag_up = true;
                mov->up = mov->up->next;
            }
            ch *= 2;
            speed += 0.0005 * time;
            is_mov_up = true;
            }
        if(!flag_down)
        if (clock1.getElapsedTime().asMicroseconds() - start > mov->down->begin) {
            if (clock1.getElapsedTime().asMicroseconds() - start > mov->down->end)
            {
                if (mov->down->next == NULL)
                    flag_down = true;
                mov->down = mov->down->next;
            }
            ch *= 3;
            speed -= 0.0005 * time;
            is_mov_down = true;
        }\
        if(!flag_right)
        if (clock1.getElapsedTime().asMicroseconds() - start > mov->right->begin ) {
            if (clock1.getElapsedTime().asMicroseconds() - start > mov->right->end)
            {
                if (mov->right->next == NULL)
                    flag_right = true;
                mov->right = mov->right->next;
            }
            ch *= 5;
            angle += time * speed / 200;
            vert.x = cos(angle);
            vert.y = sin(angle);

        }
        if(!flag_left)
        if (clock1.getElapsedTime().asMicroseconds() - start > mov->left->begin) {
            if (clock1.getElapsedTime().asMicroseconds() - start > mov->left->end)
            {
                if (mov->left->next == NULL)
                    flag_left = true;
                mov->left = mov->left->next;
            }
            ch *= 7;
            angle -= time * speed / 200;
            vert.x = cos(angle);
            vert.y = sin(angle);
        }

        if (!is_mov_down && !is_mov_up)
        {
            if (speed < 0)
                speed += 0.0003 * time;
            if (speed > 0)
                speed -= 0.0003 * time;
        }
        if (speed > 1)
            speed = 1.0;
        if (speed < -1)
            speed = -1.0;
        herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз
        if (ch % 7 == 0 && ch % 5 == 0)
            ch /= 35;
        if (ch % 2 == 0 && ch % 3 == 0)
            ch /= 6;
        /*if (ch % 10 == 0)
        {
            ch = 'j';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 65090)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle += time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                speed += 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз

            }
        }
        else if (ch % 14 == 0)
        {
            ch = 'k';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 56600)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle -= time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                speed += 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз

            }

        }
        else if (ch % 15 == 0)
        {
            ch = 'h';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 84500)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle += time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                speed -= 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз

            }

        }
        else if (ch % 21 == 0)
        {
            ch = 'g';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 93000)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle -= time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                speed -= 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз

            }

        }
        else if (ch % 2 == 0)
        {
            ch = 'w';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 28000)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                speed += 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз
            }

        }
        else if (ch % 3 == 0)
        {
            ch = 's';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 75000)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                speed -= 0.0005 * time;
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                if (speed > 1)
                    speed = 1.0;
                if (speed < -1)
                    speed = -1.0;
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз
            }
        }
        else if (ch % 5 == 0)
        {
            ch = 'd';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 112000)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle += time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз
            }
        }
        else if (ch % 7 == 0)
        {
            ch = 'a';
            move_send(ch);
            while (clock2.getElapsedTime().asMicroseconds() < 103000)
            {
                time = clock.getElapsedTime().asMicroseconds() / 800;
                clock.restart();
                angle -= time * speed / 200;
                vert.x = cos(angle);
                vert.y = sin(angle);
                if (!is_mov_down && !is_mov_up)
                {
                    if (speed < 0)
                        speed += 0.0003 * time;
                    if (speed > 0)
                        speed -= 0.0003 * time;
                }
                herosprite.move(speed * vert.x, speed * vert.y);//происходит само движение персонажа вниз

            }
        }
*/
        if(flag_down && flag_left && flag_right && flag_up && speed < 0.0003 * time)
            window.close();
        herosprite.setRotation(angle * 180 / 3.14);
        //tmpherosprite.setPosition(int(-vert.x * 67.5 + 36 * vert.y + pos.x), int(-vert.y * 67.5 - 36 * vert.x + pos.y));
       // tmpherosprite.setRotation(angle * 180 / 3.14);
        window.clear(Color(255, 255, 255));
        window.draw(herosprite);
        window.display();


    }

}
