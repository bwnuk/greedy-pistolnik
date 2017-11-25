#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animation.h"
#include "player.h"
#include "Fence.h"
#include <Windows.h>
#include <string>

using namespace std;
//using namespace sf;

class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runGame();
	
protected:
	enum GameState { MENU, GAME, SHOOTING, AUTORS, GAME_OVER, END };
	GameState state;

private:
	sf::Font font;
	
	void menu();
	void game();
	void shoot();
	void autor();
};