#include "Menu.h"

const int WIDTH = 1100;
const int HEIGHT = 720;
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Greedy Pistolnik", sf::Style::Titlebar | sf::Style::Close);
const float sizeSq = 32.0f;
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
		case GameState::AUTORS:
			autor();
			break;
		}
	}
}


void Menu::menu()
{
	sf::View viewMenu;
	sf::Texture text;

	text.loadFromFile("images/tlo.jpg");
	
	sf::RectangleShape sprait;
	sprait.setTexture(&text);
	sf::Vector2f sizeImageMenu(WIDTH, HEIGHT);
	sprait.setSize(sizeImageMenu);
	sprait.setPosition(0.0f, -100.0f);
	sprait.setScale(1.0f, 1.3f);
	
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
		tekst[i].setCharacterSize(70);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(WIDTH / 2 - tekst[i].getGlobalBounds().width / 2, 200 + i * 90); //200 + i * 70
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		while (window.pollEvent(event))
		{
			viewMenu.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
			//window.setView(viewMenu);
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
			window.setView(viewMenu);
			window.display();
	}
}

void Menu::game()
{
	//////////////////////////
	sf::Texture texture;
	sf::Texture background_texture;
	sf::Texture shop_texture;
	sf::Texture enemy_texture;
	sf::Sprite map;
	
	texture.loadFromFile("images/player.png");
	background_texture.loadFromFile("images/mapa.png");
	shop_texture.loadFromFile("images/shop.png");
	enemy_texture.loadFromFile("images/19.png");
	map.setTexture(background_texture);
	map.setPosition(0.0f, 0.0f);
	
	player player(texture, sf::Vector2u(3, 4), 2.0f, 0.1f, 140.0f);
	
	float deltatime = 0.0f;
	float timer = 0.0f;
	
	sf::Clock clock;
	sf::View view;
	sf::Vector2f sizeBG(background_texture.getSize());
	Account playerAccount;
	playerAccount.set_money(500);


	//Screen lock
	Fence upLock(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(sizeBG.x/2.0f, 0.0f));
	Fence leftLock(nullptr, sf::Vector2f(0.0f, sizeBG.y), sf::Vector2f(0.0f, sizeBG.y/2.0f));
	Fence rightLock(nullptr, sf::Vector2f(0.0f,sizeBG.y), sf::Vector2f(sizeBG.x, sizeBG.y / 2.0f));
	Fence downLock(nullptr, sf::Vector2f(sizeBG.x, 0.0f), sf::Vector2f(sizeBG.x/2.0f, sizeBG.y));
	
	//Building
	Fence building(nullptr, sf::Vector2f(13.0f * sizeSq, 9.0f * sizeSq), sf::Vector2f(13.0f * sizeSq / 2.0f, 9.0f * sizeSq / 2.0f));
	Fence door(nullptr, sf::Vector2f(2.0f * sizeSq, sizeSq), sf::Vector2f(7.0f * sizeSq, 8.0f * sizeSq + 16.0f));
	Fence mountain(nullptr, sf::Vector2f(16.0f * sizeSq, 18.0f * sizeSq), sf::Vector2f(38.0f * sizeSq, 18.0f * sizeSq / 2.0f));
	Fence enemySheriff(&enemy_texture, sf::Vector2f(2.0f * sizeSq, 2.0 * sizeSq), sf::Vector2f(48.0f * sizeSq, 18.0f * sizeSq / 2.0f));
	
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

		//Lock
		upLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		rightLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		leftLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		downLock.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		mountain.GetCollider().CheckCollision(player.GetCollider(), 1.0f);
		building.GetCollider().CheckCollision(player.GetCollider(), 1.0f);

		player.Update(deltatime);
		
		if(door.GetCollider().CheckCollision(player.GetCollider(), 1.0f) && ( player.direction == 2 ))
		{
			text("shop.txt", SHOP);
			if(state == SHOP)
				shop(player);
		}
		if (enemySheriff.GetCollider().CheckCollision(player.GetCollider(), 1.0f) && (player.direction == 2))
		{
			text("sherif.txt", SHOOT);
			if (state == SHOOT)
			{
				shoot();
				player.set_money(player.get_money() + 250);
			}
		}

		view.setCenter(player.GetPosition());
		window.clear(sf::Color::Black);
		window.draw(map);
		///
		enemySheriff.Draw(window);
		//mountain.Draw(window);
		//////////////
		upLock.Draw(window);
		leftLock.Draw(window);
		rightLock.Draw(window);
		downLock.Draw(window);
		/////////////
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
	map1.setPosition(0, -140);
	sf::View viewShoot;

	int killCounter = 0;
	sf::Text textKills("Kills: ", font, 40);

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

			switch (random)
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

			int temp_size_up = window.getSize().y / 2.0f - 100.0f;
			int temp_size_down = window.getSize().y - 300.0f;
			int temp_size_width = window.getSize().x - 100.0f;

			switch (random)
			{
			case 1:
				target1.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target1);
				break;

			case 2:
				target2.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target2);
				break;

			case 3:
				target3.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target3);
				break;

			case 4:
				target4.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target4);
				break;

			case 5:
				target5.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
				targets.push_back(target5);
				break;

			case 6:
				target6.Position(sf::Vector2f(rand() % temp_size_width + 30.0f, rand() % temp_size_down + temp_size_up));
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
					killCounter++;
					targets.erase(targets.begin() + i);
					break;
				}
			}

		}

		//Crosshair moving

		crosshairPosition.x = sf::Mouse::getPosition(window).x;
		crosshairPosition.y = sf::Mouse::getPosition(window).y;
		crosshairRect.setPosition(crosshairPosition);

		//Text
		sf::Text textKillsNumber(std::to_string(killCounter), font, 35);
		textKills.setPosition(910.0f, -90.0f);
		textKillsNumber.setPosition(1005.0f, -87.0f);

		//Drawing

		if (killCounter == 5)
		{
			std::cout << 407;
			return;

		}


		window.clear();
		window.draw(map1);
		for (size_t i = 0; i < targets.size(); i++)
		{

			window.draw(targets[i].body);
		}

		viewShoot.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
		window.setView(viewShoot);
		window.draw(gun);
		window.draw(textKills);
		window.draw(textKillsNumber);
		window.draw(crosshairRect);
		window.display();
	}
}

void Menu::shop(player & p1)
{

	sf::View viewShoot;
	sf::Texture texture;
	texture.loadFromFile("images/shop.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	sprite.setScale(sf::Vector2f(0.8f, 1.5f));
	sprite.setPosition(30, -200);
	const int arraysize = 6;
	sf::Text adam("Adam", font, 60);
	std::vector<sf::Text> texts;
	sf::Text text[arraysize];
	std::string shop_text[arraysize] = { "100$", "200$", "300$", "400$", "999$", "Wyjdz"};


	for (int i = 0; i < arraysize - 1; i++)
	{
		adam.setFont(font);
		adam.setCharacterSize(60);
		adam.setString(shop_text[i]);
		adam.setPosition(80 + i * 200, 640);
		texts.push_back(adam);
	}
	adam.setFont(font);
	adam.setCharacterSize(60);
	adam.setString(shop_text[5]);
	adam.setPosition(100.0f, 0.0f);
	texts.push_back(adam);

	while (window.isOpen())
	{
		sf::Vector2f mausePos(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y + 90.0f);
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
			default:
				break;
			}
		}

		viewShoot.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
		window.setView(viewShoot);

		for (int i = 0; i<texts.size() - 1; i++)
			if (texts[i].getGlobalBounds().contains(mausePos))
			{
				texts[i].setFillColor(sf::Color::Red);
			}
			else texts[i].setFillColor(sf::Color::White);
			mausePos.x = sf::Mouse::getPosition(window).x; 
			mausePos.y = sf::Mouse::getPosition(window).y - 50.0f;
			if (texts[5].getGlobalBounds().contains(mausePos))
			{
				texts[5].setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					return;
			}
			else texts[5].setFillColor(sf::Color::White);
			window.clear();
			window.draw(sprite);

			for (int i = 0; i < texts.size(); i++)
			{
				window.draw(texts[i]);
			}
			window.draw(p1.AccountText);
			window.draw(p1.AccountTextMoney);
			window.display();

	}
}

void Menu::autor()
{
	sf::Text title("Autorzy :", font, 90);
	title.setStyle(sf::Text::Bold);

	title.setPosition(WIDTH / 4 - title.getGlobalBounds().width / 2, 20);
	sf::View viewAutor;

	const int ile = 5;

	sf::Text tekst[ile];

	std::string aut[] = { "Jan Szewczyk","Bartlomiej Wnuk", "Tu Trong Manh", "Andrzej Ustupski", "back" };
	for (int i = 0; i<ile; i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(70);

		if (i == 4)
		{
			tekst[i].setString(aut[i]);
			tekst[i].setPosition(WIDTH /4.0f * 3.0f - tekst[i].getGlobalBounds().width / 2.0f, 150.0f + i *110.0f);
			continue;
		}

		tekst[i].setString(aut[i]);
		tekst[i].setPosition(WIDTH / 2.0f - tekst[i].getGlobalBounds().width / 2.0f, 150.0f + i * 90.0f);
	}


	while (state == AUTORS && window.isOpen())
	{
		viewAutor.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		mouse.y = mouse.y + 90.0f;
		sf::Event event;
	
		while (window.pollEvent(event))
		{
			//klikniêcie EXIT
			if (tekst[4].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			{
				state = MENU;
			}
		}

		if (tekst[4].getGlobalBounds().contains(mouse))
			tekst[4].setFillColor(sf::Color::Red);
		else 
			tekst[4].setFillColor(sf::Color::White);
		window.clear();
		window.setView(viewAutor);
		window.draw(title);
		for (int i = 0; i<ile; i++)
			window.draw(tekst[i]);
		window.display();
	}


}

void Menu::text(std::string t, GameState k)
{
	std::fstream file(t, std::ios::in);
	const int CHATPOSITION = 600;
	sf::View viewChat;
	sf::Texture winChat;
	winChat.loadFromFile("images/chat2.jpg");
	sf::Sprite sprait;
	sprait.setTexture(winChat);
	sprait.setScale(sf::Vector2f(0.83f, 0.83f));
	sprait.setPosition(-10, CHATPOSITION);
	sprait.setScale(1.8, 1.8);

		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;

		const int ile = 4;

		sf::Text tekst[ile];
		std::string str[4];
		int i = 0;
		if (file.good())
		{
			while (!file.eof())
			{
				getline(file, str[i]);
				i++;
			}
		}
		file.close();
		for (int i = 0; i < ile; i++)
		{
			tekst[i].setFont(font);
			tekst[i].setCharacterSize(20);

			tekst[i].setString(str[i]);
			tekst[i].setPosition(100, CHATPOSITION + 20 + i * 50); //
		}
		window.setMouseCursorVisible(true);
		while (window.isOpen())
		{

			sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
			mouse.y = mouse.y + 120.0f;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (tekst[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					state = k;
					return;
				}
				else if (tekst[3].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
				{
					state = GAME;
					return;
				}

			}


			for (int i = 2; i < ile; i++)
			{
				if (tekst[i].getGlobalBounds().contains(mouse))
					tekst[i].setFillColor(sf::Color::Red);
				else tekst[i].setFillColor(sf::Color::White);
			}
			//window.clear();
			viewChat.setCenter(WIDTH / 2.0f, HEIGHT / 2.0f);
			window.setView(viewChat);
			window.draw(sprait);
			for (int i = 0; i < ile; i++)
				window.draw(tekst[i]);
			window.display();
		}
}