#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class Core : public sf::RenderWindow
{
public:
	Core();
	virtual ~Core();

	void		load(const std::string & filename);
	void		create();
	bool		isSynchronized();
	sf::Clock	getClock() const;


private:
	sf::Clock		clock;
	sf::Time		lastTime;
};