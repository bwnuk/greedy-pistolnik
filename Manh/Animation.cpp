#include "Animation.h"



Animation::Animation(sf::Texture & texture, sf::Vector2u imageCount, float switchtime)
{
	this->imageCount = imageCount;
	this->switchtime = switchtime;
	totaltime = 0.0f;
	currentImage.x = 0;
	uvRect.width = texture.getSize().x / (float)imageCount.x;
	uvRect.height = texture.getSize().y / (float)imageCount.y;
}


Animation::~Animation()
{
}

void Animation::Update(unsigned int row, float deltaTime, bool Stay, float turboSpeed)
{

	currentImage.y = row;
	totaltime += deltaTime;
	if (totaltime >= switchtime/turboSpeed)
	{
		totaltime -= switchtime/turboSpeed;
		currentImage.x++;
		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}
	uvRect.top = currentImage.y*uvRect.height;
	if(Stay)
		uvRect.left = 0 * uvRect.width;
	else
		uvRect.left = currentImage.x*uvRect.width;
}
