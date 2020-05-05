#include "Control.h"
#include "Common.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Control::Control()
{
	this->controls["Left"] = sf::Keyboard::Q;
	this->controls["Right"] = sf::Keyboard::D;
	this->controls["Up"] = sf::Keyboard::Z;
	this->controls["Down"] = sf::Keyboard::S;

	this->controls["Shoot"] = sf::Keyboard::Return;
	this->controls["Leave"] = sf::Keyboard::Escape;

	this->load(C_CONFIG("Control.cfg"));
}

Control::~Control()
{

}

void	Control::load(const std::string & filename)
{
	std::ifstream		infile(filename);
	std::string			line;
	std::size_t			pos;

	std::string			key;
	std::string			value;

	while (std::getline(infile, line))
	{
		pos = line.find(":");
		if (pos != std::string::npos)
		{
			key = line.substr(0, pos);
			value = line.substr(pos + 1, line.size());

			for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			{
				if (static_cast<sf::Keyboard::Key>(i) == std::stoi(value))
					this->controls[key] = static_cast<sf::Keyboard::Key>(i);
			}
		}
	}
}

sf::Keyboard::Key	Control::getKey(const std::string & name) 
{
	if (this->controls.find(name) == this->controls.end())
		return (sf::Keyboard::Unknown);
	return (this->controls[name]);
}