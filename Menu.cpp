#include "Menu.h"

const int WIDTH = 1100;
const int HEIGHT = 720;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Greedy Pistolnik", sf::Style::Titlebar | sf::Style::Close);

Menu::Menu(void)
{
	state = END;

	if (!font.loadFromFile("images/jendrzej.ttf"))
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
			game();
			break;
		case GameState::SHOOTING:
			shoot();
		case GameState::AUTORS:
			autor();
			break;
		}
	}
}


void Menu::menu()
{
	sf::Texture text;
	text.loadFromFile("images/tlo.jpg");
	sf::RectangleShape sprait;
	sprait.setTexture(&text);
	sf::Vector2f sizeImageMenu(WIDTH, HEIGHT);
	sprait.setSize(sizeImageMenu);
	sf::Text title("Greedy Pistolnik", font, 80);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Yellow);
	title.setPosition(WIDTH / 2 - title.getGlobalBounds().width / 2, 100.0f);

	const int ile = 3;

	sf::Text tekst[ile];

	std::string str[] = { "Graj","Autorzy","Exit" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(60);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(WIDTH / 2 - tekst[i].getGlobalBounds().width / 2, 250 + i * 120);
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		while (window.pollEvent(event))
		{
			//Wciœniêcie ESC lub przycisk X
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Escape)
				state = END;
			//Autorzy
			else if (tekst[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = GAME;
			}
			else if (tekst[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				std::cout << tekst[1].getGlobalBounds().top;
				std::cout << tekst[1].getGlobalBounds().left;
				state = AUTORS;
			}
			//klikniêcie EXIT
			else if (tekst[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = END;
			}
		}
	

		for (int i = 0; i<ile; i++)
			if (tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setFillColor(sf::Color::Red);
			else tekst[i].setFillColor(sf::Color::White);

			window.clear();

			window.draw(sprait);
			window.draw(title);

			for (int i = 0; i<ile; i++)
				window.draw(tekst[i]);

			window.display();
	}
}

void Menu::game()
{
	//////////////////////////
	sf::Texture texture;
	texture.loadFromFile("images/player.png");
	sf::Texture background_texture;
	background_texture.loadFromFile("images/background.jpg");
	sf::Sprite map;
	map.setTexture(background_texture);
	player player(texture, sf::Vector2u(3, 4), 2.0f, 0.1f, 140.0f);
	float deltatime = 0.0f;
	float timer = 0.0f;
	sf::Clock clock;
	sf::View view;
	Fence fence1(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 0.0f));
	Fence fence2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(200.0f + player.collisionSize, 0.0f));
	Fence fence3(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 200.0f + player.collisionSize));
	//Fence fence2(nullptr, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(0.0f, 272.0f));
	while (window.isOpen())
	{
		deltatime = clock.restart().asSeconds();
		sf::Event zdarzenie;
		while (window.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				window.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				window.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
				window.close();
		}
		player.Update(deltatime);
		fence1.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		if (fence2.GetCollider().CheckCollision(player.GetCollider(), 1.0f))
		{
			state = SHOOTING;
			return;
		}
		fence3.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		view.setCenter(player.GetPosition());

		window.clear(sf::Color::Black);
		window.draw(map);
		fence1.Draw(window);
		fence2.Draw(window);
		fence3.Draw(window);
		player.Draw(window, view);
		window.display();
	}
}

void Menu::shoot()
{
	sf::Texture background_texture1;
	background_texture1.loadFromFile("images/shootBCG1.jpg");
	sf::Sprite map1;
	map1.setTexture(background_texture1);
	map1.setScale(sf::Vector2f(1.2f, 1.6f));
	map1.setPosition(0,-140);
	sf::View viewShoot;

	srand(time(NULL));

	//Window
	window.setFramerateLimit(60);

	//Gun
	sf::RectangleShape gun(sf::Vector2f(50.0f, 100.0f));
	sf::Texture gunTexture;
	gunTexture.loadFromFile("images/strzelba.png");
	gun.setTexture(&gunTexture);
	gun.setOrigin(gun.getSize() / 2.0f);
	gun.setPosition(WIDTH / 2.0f, HEIGHT + 50.0f);

	int spawnCounter = 0;

	//Targets
	sf::Texture targetTexture1;
	sf::Texture targetTexture2;
	sf::Texture targetTexture3;
	sf::Texture targetTexture4;
	sf::Texture targetTexture5;
	sf::Texture targetTexture6;

	std::vector<enemy> targets;

	//

	//Wektory, potrzebne
	sf::Vector2f gunCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2f aimDirection;
	sf::Vector2f aimDirectionNormal;

	//Crosshair
	sf::Texture crosshairTexture;
	sf::RectangleShape crosshairRect(sf::Vector2f(160.0f, 160.0f));
	sf::Vector2f crosshairPosition;

	crosshairTexture.loadFromFile("images/crosshair.png");
	crosshairRect.setTexture(&crosshairTexture);
	crosshairRect.setOrigin(crosshairRect.getSize() / 2.0f);


	window.setMouseCursorVisible(false);

	while (window.isOpen()) {
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

		if (spawnCounter < 40)
			spawnCounter++;

		if (spawnCounter >= 40 && targets.size() < 10)
		{
			//Random texture spawning

			int random = rand() % 6 + 1;

			spawnCounter = 0;

			switch(random)
			{
			case 1:
				targetTexture1.loadFromFile("images/10.png");	
				break;
			
			case 2:
				targetTexture2.loadFromFile("images/11.png");
				break;
			
			case 3:
				targetTexture3.loadFromFile("images/12.png");
				break;
			
			case 4:
				targetTexture4.loadFromFile("images/13.png");
				break;
			
			case 5:
				targetTexture5.loadFromFile("images/14.png");
				break;
			
			case 6:
				targetTexture6.loadFromFile("images/14.png");
				break;
			}
			
			enemy target1(targetTexture1);
			enemy target2(targetTexture2);
			enemy target3(targetTexture3);
			enemy target4(targetTexture4);
			enemy target5(targetTexture5);
			enemy target6(targetTexture6);

			int temp_size_up = window.getSize().y / 2.0f - 120.0f;
			int temp_size_down = window.getSize().y - 300.0f;
			int temp_size_width = window.getSize().x - 50.0f;

			switch (random)
			{
			case 1:
				target1.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target1);
				break;

			case 2:
				target2.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target2);
				break;

			case 3:
				target3.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target3);
				break;

			case 4:
				target4.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target4);
				break;

			case 5:
				target5.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target5);
				break;

			case 6:
				target6.Position(sf::Vector2f(rand() % temp_size_width + 50.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target6);
				break;
			}
			
		}

		//Shooting

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (size_t i = 0; i < targets.size(); i++)
			{
				if (targets[i].body.getGlobalBounds().contains(mousePosWindow))
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
		window.draw(map1);
		for (size_t i = 0; i < targets.size(); i++)
		{

			window.draw(targets[i].body);
		}

		viewShoot.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
		window.setView(viewShoot);
		window.draw(gun);
		window.draw(crosshairRect);
		window.display();
	}
}

void Menu::autor()
{
	sf::Text title("Autorzy :", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(WIDTH / 4 - title.getGlobalBounds().width / 2, 20);


	const int ile = 4;

	sf::Text tekst[ile];

	std::string aut[] = { "Jan Szewczyk","Bartlomiej Wnuk", "Tu Trong Manh", "back" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(70);

		if (i == 3)
		{
			tekst[i].setString(aut[i]);
			tekst[i].setPosition(WIDTH /4.0f * 3.0f - tekst[i].getGlobalBounds().width / 2.0f, 150.0f + i *110.0f);
			continue;
		}

		tekst[i].setString(aut[i]);
		tekst[i].setPosition(WIDTH / 2.0f - tekst[i].getGlobalBounds().width / 2.0f, 150.0f + i * 90.0f);
	}


	while (state == AUTORS)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
	
		while (window.pollEvent(event))
		{
			
			//klikniêcie EXIT
			if (tekst[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				state = MENU;
			}
		}

		if (tekst[3].getGlobalBounds().contains(mouse))
			tekst[3].setFillColor(sf::Color::Red);
		else tekst[3].setFillColor(sf::Color::White);
		
			window.clear();

			window.draw(title);
			for (int i = 0; i<ile; i++)
				window.draw(tekst[i]);

			window.display();
	}


}