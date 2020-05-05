#include "Core.h"
#include "Common.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

std::string winTitle;
float		winWidth;
float		winHeight;
bool		winFullscreen;
bool		winFps;

Core::Core()
{
	winWidth = 1280;
	winHeight = 720;
	winTitle = "R-Type #EpiBros";
	winFullscreen = false;
	winFps = false;
}

Core::~Core()
{

}

void	Core::create()
{
	if (winFullscreen)
		sf::RenderWindow::create(sf::VideoMode(static_cast<unsigned int>(winWidth),
			static_cast<unsigned int>(winHeight)), winTitle, sf::Style::Fullscreen);
	else
		sf::RenderWindow::create(sf::VideoMode(static_cast<unsigned int>(winWidth),
			static_cast<unsigned int>(winHeight)), winTitle);
}

bool	Core::isSynchronized()
{
	sf::Time elapsed = this->clock.getElapsedTime();

	if (elapsed.asMilliseconds() > lastTime.asMilliseconds() + F_LIMIT)
	{
		this->lastTime = elapsed;
		return (true);
	}
	return (false);
}

sf::Clock	Core::getClock() const
{
	return (this->clock);
}

void	Core::load(const std::string & filename)
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

			if (!key.empty() && !value.empty())
			{
				winWidth = key == "Width" ? std::stoi(value) : winWidth;
				winHeight = key == "Height" ? std::stoi(value) : winHeight;
				winTitle = key == "Title" ? value : winTitle;
				winFullscreen = key == "Fullscreen" ? value == "true" ? 1 : 0 : winFullscreen;
				winFps = key == "Fps" ? value == "true" ? 1 : 0 : winFps;
			}
		}
	}
}