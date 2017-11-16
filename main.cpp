// zad.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Fence.h"

static const float VIEW_HEIGHT = 400;
static const float VIEW_WIDTH = 800;

void ResizeView(const sf::RenderWindow& window, sf::View & view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT, 32), "DUDUDUD", sf::Style::Close | sf::Style::Resize);
	sf::Texture playerTexture;
	playerTexture.loadFromFile("player_layout.png");
	sf::Texture background_texture;
	background_texture.loadFromFile("background.jpg");
	sf::Sprite map;
	map.setTexture(background_texture);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH, VIEW_HEIGHT));

	Fence fence1(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(500.0f, 100.0f));
	Fence fence2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(100.0f, 0.0f));

	Player player(&playerTexture, sf::Vector2u(4, 4), 0.1f, 150.0f);

	float deltatime = 0.0f;
	sf::Clock clock;
	while (window.isOpen())
	{
		deltatime = clock.restart().asSeconds();
		sf::Event zdarzenie;
		while (window.pollEvent(zdarzenie))
		{
			switch (zdarzenie.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (zdarzenie.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;
			default:
				break;
			}

		}
		player.Update(deltatime);

		fence1.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		fence2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

		window.clear(sf::Color::Black);
		window.draw(map);
		player.Draw(window);
		fence1.Draw(window);
		fence2.Draw(window);
		window.display();
	}

	return 0;
}