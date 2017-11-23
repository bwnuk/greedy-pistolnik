#include "stdafx.h"
#include "Menu.h"

RenderWindow window(VideoMode(1280, 720), "Greedy Pistolnik",Style::Fullscreen);

Menu::Menu(void)
{
	state = END;

	if (!font.loadFromFile("jendrzej.ttf"))
	{
		return;
	}

	state = MENU;
}


Menu::~Menu(void)
{
}


void Menu::runGame()
{
	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			//
			break;
		case GameState::AUTORS:
			autor();
			break;
		}
	}
}


void Menu::menu()
{
	Texture text;
	text.loadFromFile("tlo.jpg");
	Sprite sprait;
	sprait.setTexture(text);
	sprait.setScale(sf::Vector2f(0.83f, 0.83f));

	Text title("Greedy Pistolnik", font, 90);
	title.setStyle(Text::Bold);

	title.setPosition(1280 / 2 - title.getGlobalBounds().width / 2, 20);

	const int ile = 3;

	Text tekst[ile];

	string str[] = { "Graj","Autorzy","Exit" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(60);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280 / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			//Autorzy
			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = AUTORS;
			}
			//klikniêcie EXIT
			else if (tekst[2].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
	

		for (int i = 0; i<ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(Color::Red);
			else tekst[i].setFillColor(Color::White);

			window.clear();

			window.draw(sprait);
			window.draw(title);

			for (int i = 0; i<ile; i++)
				window.draw(tekst[i]);

			window.display();
	}
}

void Menu::autor()
{
	Text title("Autorzy :", font, 90);
	title.setStyle(Text::Bold);

	title.setPosition(1280 / 4 - title.getGlobalBounds().width / 2, 20);


	const int ile = 5;

	Text tekst[ile];

	string aut[] = { "Jan Szewczyk","Bartłomiej Wnuk", "Tu Trong Manh", "Andrzej jakistam", "back" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(70);

		if (i == 4)
		{
			tekst[i].setString(aut[i]);
			tekst[i].setPosition(1280 /4*3 - tekst[i].getGlobalBounds().width / 2, 150 + i *110);
			continue;
		}

		tekst[i].setString(aut[i]);
		tekst[i].setPosition(1280 / 2 - tekst[i].getGlobalBounds().width / 2, 150 + i * 90);
	}


	while (state == AUTORS)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;
	
		while (window.pollEvent(event))
		{
			
			//klikniêcie EXIT
			if (tekst[4].getGlobalBounds().contains(mouse) && event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left || event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				state = MENU;
			}
		}

		if (tekst[4].getGlobalBounds().contains(mouse))
			tekst[4].setFillColor(Color::Red);
		else tekst[4].setFillColor(Color::White);
		
			window.clear();

			window.draw(title);
			for (int i = 0; i<ile; i++)
				window.draw(tekst[i]);

			window.display();
	}


}