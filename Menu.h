#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "player.h"
#include "Fence.h"
#include "Account.h"
#include "enemy.h"
#include <Windows.h>
#include <string>
#include <fstream>
#include <ctime>

class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runGame();
	
protected:
	enum GameState { MENU, GAME, SHOP, SHOOT, AUTORS, GAME_OVER, END };
	GameState state;

private:
	bool lose;
	sf::Font font;
	
	void menu();
	void game();
	void shoot();
	void shop(player &p1);
	void autor();
	void text(std::string t, GameState k);
};