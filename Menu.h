#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "player.h"
#include "Fence.h"
#include "enemy.h"
#include <Windows.h>
#include <string>
#include <fstream>
class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runGame();
	
protected:
	enum GameState { MENU, GAME, SHOP, AUTORS, GAME_OVER, END };
	GameState state;

private:
	sf::Font font;
	
	void menu();
	void game();
	void shoot();
	void shop();
	void autor();
	void text();
};