#include "Text.h"
#include <iostream>
#include <string>

Text::Text(const std::string & name)
	: sf::Text()
{
	if (this->font.loadFromFile(name))
	{
		this->setFont(this->font);
		this->setCharacterSize(44);
		this->setFillColor(sf::Color::White);
	}
}

Text::~Text()
{

}