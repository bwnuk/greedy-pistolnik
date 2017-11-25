#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "player.h"
#include "Fence.h"
#include "enemy.h"
#include <Windows.h>
#include <string>

class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runGame();
	
protected:
	enum GameState { MENU, GAME, SHOOTING,SHOP, AUTORS, GAME_OVER, END };
	GameState state;

private:
	sf::Font font;
	
	void menu();
	void game();
	void shop();
	void shoot();
	void autor();
};