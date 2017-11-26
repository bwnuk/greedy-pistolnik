#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Account
{
public:
	Account();
	~Account();
	void set_money(int m);
	int get_money();
private:
	int money;
};

