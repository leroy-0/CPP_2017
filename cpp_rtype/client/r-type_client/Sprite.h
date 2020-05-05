#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Sprite : public sf::Sprite
{
	public:
		Sprite(const std::string & name);
		virtual ~Sprite();

	private:
		sf::Texture texture;
};