#pragma once

#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

class Menu
{
public:
	Menu(void);
	~Menu(void);

	void runGame();
	
protected:
	enum GameState { MENU, GAME, AUTORS, GAME_OVER, END };
	GameState state;

private:
	Font font;
	
	void menu();
	void autor();
};