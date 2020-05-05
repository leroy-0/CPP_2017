#include "Sprite.h"

Sprite::Sprite(const std::string & name)
	: sf::Sprite()
{
	if (this->texture.loadFromFile(name))
	{
		this->setTexture(this->texture);
	}
}

Sprite::~Sprite()
{

}