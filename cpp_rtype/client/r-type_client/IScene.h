#pragma once

#include "SFML/Graphics.hpp"
#include "Common.h"

class IScene
{
public:
	virtual ~IScene() {};

	virtual mod		run(sf::RenderWindow & window) = 0;
	virtual mod		events(const sf::Event & event) = 0;
	virtual void	start() = 0;
	virtual void	stop() = 0;
};