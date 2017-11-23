#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "player.h"
#include "Fence.h"
int main()
{
	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 600, 32), "Pistols");
	sf::Texture texture;
	texture.loadFromFile("player2.png");
	sf::Texture background_texture;
	background_texture.loadFromFile("background.png");
	sf::Sprite map;
	map.setTexture(background_texture);
	player player(texture, sf::Vector2u(9,4), 2.0f, 0.09f, 140.0f);
	float deltatime = 0.0f;
	float timer = 0.0f;
	sf::Clock clock;
	sf::View view;
	Fence fence1(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 0.0f));
	Fence fence2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f+player.collisionSize, 0.0f));
	Fence fence3(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 200.0f+player.collisionSize));
	//Fence fence2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 272.0f));
	while (oknoAplikacji.isOpen())
	{
		deltatime = clock.restart().asSeconds();
		sf::Event zdarzenie;
		while (oknoAplikacji.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
				oknoAplikacji.close();
		}
		player.Update(deltatime);
		view.setCenter(player.GetPosition());
		fence1.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		fence2.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		fence3.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		view.setCenter(player.GetPosition());
		oknoAplikacji.clear(sf::Color::Black);
		oknoAplikacji.draw(map);
		fence1.Draw(oknoAplikacji);
		fence2.Draw(oknoAplikacji);
		fence3.Draw(oknoAplikacji);
		player.Draw(oknoAplikacji, view);
		oknoAplikacji.display();
	}
	return 0;
}