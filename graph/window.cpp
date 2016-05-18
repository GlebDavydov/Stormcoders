#include <SFML/Graphics.hpp>
#include "keys.h"
#include "move.h"
#include "drive.h"

#include "realTimeMove.h"
using namespace sf;

int menu(RenderWindow & window) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	Image first_b;
	first_b.loadFromFile("111.png");
    menuTexture1.loadFromImage(first_b);
	menuTexture2.loadFromFile("222.png");
	menuTexture3.loadFromFile("333.png");
	aboutTexture.loadFromFile("about.png");
	menuBackground.loadFromFile("pipboy.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		window.clear(Color(129, 181, 221));

		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		if (IntRect(130, 50, 200, 30).contains(Mouse::getPosition(window))) { menu1.setColor(Color(19, 0, 255)); menuNum = 1; }
		if (IntRect(130, 100, 150, 30).contains(Mouse::getPosition(window))) { menu2.setColor(Color(19, 0, 255)); menuNum = 2; }
		if (IntRect(130, 150, 45, 30).contains(Mouse::getPosition(window))) { menu3.setColor(Color(19, 0, 255)); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
                realTimeMove(window);
			if (menuNum == 2) {
                    //realTimeMove(window);
                add_way(window);
            }
			if (menuNum == 3)  {
			     window.close();
			     isMenu = false;
            }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}
