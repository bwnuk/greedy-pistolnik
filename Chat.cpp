#include "stdafx.h"
#include "Chat.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
const int CHATPOSITION = 500;
sf::RenderWindow window(sf::VideoMode(1280, 720), "Greedy Pistolnik", sf::Style::Titlebar | sf::Style::Close);

Chat::Chat()
{
	if (!font.loadFromFile("images/jendrzej.ttf"))
	{
		return;
	}
}


Chat::~Chat()
{
}


void Chat::startChat()
{
	sf::Texture winChat;
	winChat.loadFromFile("chat2.jpg");
	sf::Sprite sprait;
	sprait.setTexture(winChat);
	sprait.setScale(sf::Vector2f(0.83f, 0.83f));
	sprait.setPosition(-10, CHATPOSITION);
	sprait.setScale(1.8, 1.8);


	while (1)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		const int ile = 4;

		sf::Text tekst[ile];

		std::string str[] = { "ja:witaj skurwysynie:","On: Witaj tempy chuju!!! DAwaj Pieni¹dze albo w ryj","ja: Wypierdalaj za brame ", "ja: Jestem chujkiem, masz pieniadze" };
		for (int i = 0; i < ile; i++)
		{
			tekst[i].setFont(font);
			tekst[i].setCharacterSize(30);

			tekst[i].setString(str[i]);
			tekst[i].setPosition(100, CHATPOSITION + 20 + i * 50);
		}

		

		while (1)
		{
			
			sf::Vector2f mouse(sf::Mouse::getPosition(window));
			sf::Event event;

			while (window.pollEvent(event))
			{
				if (tekst[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					return;
				}
				else if (tekst[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					return;
				}
				
			}


			for (int i = 2; i < ile; i++)
			{
				if (tekst[i].getGlobalBounds().contains(mouse))
					tekst[i].setFillColor(sf::Color::Red);
				else tekst[i].setFillColor(sf::Color::White);
			}
				window.clear();
				window.draw(sprait);

				for (int i = 0; i < ile; i++)
					window.draw(tekst[i]);
				
				window.display();
		}
	}
}
