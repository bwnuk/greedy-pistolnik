// plik.cpp : Defines the entry point for the console application.
//

#include <SFML/Graphics.hpp>
#include "SFML\Window.hpp"
#include "SFML\System.hpp"
#include <math.h>
#include <iostream>
#include <vector>
#include <cstdlib>

int main()
{
	srand(time(NULL));

	//Window
	sf::RenderWindow window(sf::VideoMode(800, 600), "MAGIC", sf::Style::Default);
	window.setFramerateLimit(60);

	//Gun
	sf::RectangleShape gun(sf::Vector2f(50.0f, 100.0f));
	sf::Texture gunTexture;
	gunTexture.loadFromFile("strzelba.png");
	gun.setTexture(&gunTexture);
	gun.setOrigin(gun.getSize() / 2.0f);
	gun.setPosition(400, 550);

	int spawnCounter = 0;

	//Targets
	sf::RectangleShape target;
	target.setFillColor(sf::Color::Blue);
	target.setSize(sf::Vector2f(50.f, 50.f));

	std::vector<sf::RectangleShape> targets;

	//Wektory, potrzebne
	sf::Vector2f gunCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormal;

	//Crosshair
	sf::Texture crosshairTexture;
	sf::RectangleShape crosshairRect(sf::Vector2f(160.0f, 160.0f));
	sf::Vector2f crosshairPosition;

	crosshairTexture.loadFromFile("crosshair.png");
	crosshairRect.setTexture(&crosshairTexture);
	crosshairRect.setOrigin(crosshairRect.getSize() / 2.0f);


	window.setMouseCursorVisible(false);

	while (window.isOpen())	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::Resized:
				/*ResizeView(window, view);*/
				break;
			default:
				break;
			}

		}

		//Liczymy wektory

		gunCenter = sf::Vector2f(gun.getPosition().x, gun.getPosition().y);
		mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(window));
		aimDirection = mousePosWindow - gunCenter;
		aimDirectionNormal = aimDirection / sqrt(pow(aimDirection.x, 2) + pow(aimDirection.y, 2));

		//Enemies

		if (spawnCounter < 30)
			spawnCounter++;

		if (spawnCounter >= 30 && targets.size() < 10)
		{
			spawnCounter = 0;

			target.setPosition(sf::Vector2f(rand() % window.getSize().x, rand() % window.getSize().y));
			targets.push_back(target);
		}

		//Shooting

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (size_t i = 0; i < targets.size(); i++)
			{
				if (targets[i].getGlobalBounds().contains(mousePosWindow))
				{
					targets.erase(targets.begin() + i);
					break;
				}
			}

		}

		//Crosshair moving

		crosshairPosition.x = sf::Mouse::getPosition(window).x;
		crosshairPosition.y = sf::Mouse::getPosition(window).y;
		crosshairRect.setPosition(crosshairPosition);

		//Drawing

		window.clear();
		for (size_t i = 0; i < targets.size(); i++)
		{

			window.draw(targets[i]);
		}
		window.draw(gun);
		window.draw(crosshairRect);

		window.display();
	}

	return 0;
}
