#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class Control
{
public:
	Control();
	virtual ~Control();

	sf::Keyboard::Key	getKey(const std::string & name);
	void				load(const std::string & filename);
private:
	std::map<std::string, sf::Keyboard::Key>	controls;
};