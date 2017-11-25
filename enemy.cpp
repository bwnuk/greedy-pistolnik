#include "stdafx.h"
#include "enemy.h"
#include <iostream> //wypierdolic

enemy::enemy(sf::Texture &enemy_texture)
{
	this->enemy_texture = enemy_texture;
	
	//body.setPosition(sf::Vector2f(rand() % 1280, rand() % 720)); // tutaj zrobic nie stale wartosci tylko zalezne od okna
	int i = rand() % 800;
	std::cout << i << std::endl;

	int random = rand() % 3 + 1;
	switch (random) 
	{
	case 1:
		sizeBody = sf::Vector2f(enemy_texture.getSize());
		sizeBody.x = sizeBody.x*0.435;
		body.setSize(sizeBody);
		body.setTexture(&enemy_texture);
		body.setTextureRect(sf::IntRect(0, 0, ceil(sizeBody.x), ceil(sizeBody.y)));
		break;
	case 2:
		sizeBody = sf::Vector2f(enemy_texture.getSize());
		tempsize = sf::Vector2f(enemy_texture.getSize());
		sizeBody.y = sizeBody.y*0.8;
		sizeBody.x = sizeBody.x*0.347;
		body.setSize(sizeBody);
		body.setTexture(&enemy_texture);
		body.setTextureRect(sf::IntRect(ceil(tempsize.x*0.435), 0, ceil(sizeBody.x), ceil(sizeBody.y))); 
	case 3:
		sizeBody = sf::Vector2f(enemy_texture.getSize());
		tempsize = sf::Vector2f(enemy_texture.getSize());
		sizeBody.y = sizeBody.y*0.5;
		sizeBody.x = sizeBody.x*0.218;
		body.setSize(sizeBody);
		body.setTexture(&enemy_texture);
		body.setTextureRect(sf::IntRect(ceil(tempsize.x*0.435 + tempsize.x*0.347), 0, ceil(sizeBody.x), ceil(sizeBody.y))); 
		break;

	default:
		exit(0);
	}
}


void enemy::set_name(std::string n)
{
	name = n;
}

std::string enemy::get_name()
{
	return name;
}

void enemy::set_hp(int h)
{
	hp = h;
}

int enemy::get_hp()
{
	return hp;
}

void enemy::set_lvl(int l)
{
	lvl = l;
}

int enemy::get_lvl()
{
	return lvl;
}

void enemy::set_speed(double s)
{
	speed = s;
}

double enemy::get_speed()
{
	return speed;
}

void enemy::Draw(sf::RenderWindow &window)
{
	window.draw(body);
}

enemy::~enemy()
{
}

void enemy::Position(sf::Vector2f pos)
{
	body.setPosition(pos);
}

