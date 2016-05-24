#include <SFML/Graphics.hpp>
#include "keys.h"
#include "move.h"
#include "drive.h"
#include <strings.h>
#include <vector>
#include <list>
#include <iostream>
#include "realTimeMove.h"


using namespace sf;

std::string some_func(int num);

class text{
public:
    Text way;
    int way_num;
    std::string strg;
    text(std::string str, int num){
        strg = str;
        way_num = num;
        way.setString(str);
        way.setCharacterSize(25);
        way.setColor(Color::White);
        way.setPosition( 100, 50);
    }
};

class Texts{
public:
    std::vector<text *> texts;
    int way_count;
    Texts(){
        way_count = 0;

    }
};

void write_way(Texts *texts);
void choose_way(RenderWindow &window, Texts *texts, Sprite bg);

int menu(RenderWindow & window) {
	Texture menuBackground;
	menuBackground.loadFromFile("pipboy.jpg");
	Sprite menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
    Texts *texts = new Texts();
	Font font;
    font.loadFromFile("arial.ttf");

	Text load_way, start_new_riding, exit, add_new_way;
    load_way.setFont(font);
    start_new_riding.setFont(font);
    exit.setFont(font);
    add_new_way.setFont(font);
    load_way.setCharacterSize(25);
    start_new_riding.setCharacterSize(25);
    exit.setCharacterSize(25);
    add_new_way.setCharacterSize(25);
    load_way.setString("Load ways");
    add_new_way.setString("Add new way");
    exit.setString("Exit");
    start_new_riding.setString("Start new riding");

	start_new_riding.setPosition(100, 50);
	add_new_way.setPosition(100, 100);
	exit.setPosition(100, 200);
	menuBg.setPosition(0, 0);
	load_way.setPosition(100, 150);

	while (isMenu)
	{
		start_new_riding.setColor(Color::White);
		add_new_way.setColor(Color::White);
		exit.setColor(Color::White);
		load_way.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (IntRect(100, 50, 200, 30).contains(Mouse::getPosition(window))) { start_new_riding.setColor(Color(19, 0, 255)); menuNum = 1; }
		if (IntRect(100, 100, 150, 30).contains(Mouse::getPosition(window))) { add_new_way.setColor(Color(19, 0, 255)); menuNum = 2; }
		if (IntRect(100, 200, 45, 30).contains(Mouse::getPosition(window))) { exit.setColor(Color(19, 0, 255)); menuNum = 3; }
		if (IntRect(100, 150, 100, 30).contains(Mouse::getPosition(window))) { load_way.setColor(Color(19, 0, 255)); menuNum = 4; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
                realTimeMove(window);
			if (menuNum == 2) {
                add_way(window);
            }
			if (menuNum == 3)  {
                window.close();
            }
            if (menuNum == 4)  {
                write_way(texts);
                choose_way(window, texts, menuBg);
            }

		}

		window.draw(menuBg);
		window.draw(start_new_riding);
		window.draw(add_new_way);
		window.draw(exit);
		window.draw(load_way);

		window.display();
	}
	return 0;
}

void write_way(Texts *texts){
    std::string textw;

    int i = 0;
    while(some_func(i).compare("") != 0){
        textw = some_func(i);
        texts->texts.push_back(new text(textw, i));
        texts->way_count++;

        i++;
    }
}

std::string some_func(int num){
    if(num == 10){
        return "";
    }
    return "some dich";
}

void choose_way(RenderWindow & window, Texts *texts, Sprite bg){
    Text tmpText;
    Font font1;
    font1.loadFromFile("arial.ttf");
    bool isChoosing = true;
    while(isChoosing){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(Keyboard::isKeyPressed(Keyboard::Escape)){
            menu(window);
        }

        window.clear(Color::Black);
        window.draw(bg);
        for(int i = 0; i < texts->way_count; i++){
            texts->texts[i]->way.setColor(Color::White);
            texts->texts[i]->way.setFont(font1);
            texts->texts[i]->way.setPosition(100, 50*(i + 1));
            if(IntRect(100, 50*(i + 1), 150, 30).contains(Mouse::getPosition(window))){
                    texts->texts[i]->way.setColor(Color(19, 0, 255));
                    if(Mouse::isButtonPressed(Mouse::Left)){
                        //do some func
                    }
            }
            window.draw(texts->texts[i]->way);
        }

        window.display();
    }
}
