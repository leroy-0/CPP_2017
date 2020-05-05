#pragma once

#include <SFML/Graphics.hpp>

class Text : public sf::Text
{
	public:
		Text::Text(const std::string & name);
		Text::~Text();

	private:
		sf::Font			font;
};