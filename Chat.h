#pragma once
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <string>
#include "stdafx.h"


class Chat
{
public:
	Chat();
	~Chat();

	void startChat();

private:
	sf::Font font;

};

