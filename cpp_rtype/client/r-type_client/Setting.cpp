#include "Setting.h"
#include <iostream>
#include <fstream>

Setting::Setting()
	: Menu()
{
	this->mymod = mod::setting;

	resolutions.push_back(sf::Vector2f(1920, 1080));
	resolutions.push_back(sf::Vector2f(1600, 900));
	resolutions.push_back(sf::Vector2f(1360, 768));
	resolutions.push_back(sf::Vector2f(1280, 720));
	resolutions.push_back(sf::Vector2f(800, 600));

	width = winWidth;
	height = winHeight;
	fullscreen = winFullscreen;
	fps = winFps;
}

Setting::~Setting()
{

}

void	Setting::start()
{
	this->choosen = 0;

	width = winWidth;
	height = winHeight;
	fullscreen = winFullscreen;
	fps = winFps;

	this->choices[0]->setString("Resolution : " +
		std::to_string(static_cast<int>(winWidth)) + " x " +
		std::to_string(static_cast<int>(winHeight)));
	this->choices[0]->setPosition(winWidth / 2 - (this->choices[0]->getGlobalBounds().width / 2),
		winHeight * 0.2f - (this->choices[0]->getGlobalBounds().height / 2));

	this->choices[1]->setString("Fullscreen : " + std::string(winFullscreen ? "On" : "Off"));
	this->choices[1]->setPosition(winWidth / 2 - (this->choices[1]->getGlobalBounds().width / 2),
		winHeight * 0.4f - (this->choices[1]->getGlobalBounds().height / 2));

	this->choices[2]->setString("FPS : " + std::string(winFps ? "On" : "Off"));
	this->choices[2]->setPosition(winWidth / 2 - (this->choices[2]->getGlobalBounds().width / 2),
		winHeight * 0.6f - (this->choices[2]->getGlobalBounds().height / 2));

	this->choices[3]->setString("Save & Quit");
	this->choices[3]->setPosition(winWidth / 2 - (this->choices[3]->getGlobalBounds().width / 2),
		winHeight * 0.8f - (this->choices[3]->getGlobalBounds().height / 2));
}

mod		Setting::getChoosen()
{
	if (this->choosen == 0)
	{
		if (this->resolutions[this->resolutions.size() - 1].x >= width
			&& this->resolutions[this->resolutions.size() - 1].y >= height)
		{
			width = this->resolutions[0].x;
			height = this->resolutions[0].y;
		}
		else
		{
			for (int i = 0; i < this->resolutions.size(); i++)
			{
				if (this->resolutions[i].x < width && this->resolutions[i].y < height)
				{
					width = this->resolutions[i].x;
					height = this->resolutions[i].y;
					break;
				}
			}
		}
		this->choices[0]->setString("Resolution : " +
			std::to_string(static_cast<int>(width)) + " x " +
			std::to_string(static_cast<int>(height)));
	}
	else if (this->choosen == 1)
	{
		fullscreen = fullscreen ? 0 : 1;
		this->choices[1]->setString("Fullscreen : " + std::string(fullscreen ? "On" : "Off"));
	}
	else if (this->choosen == 2)
	{
		fps = fps ? 0 : 1;
		this->choices[2]->setString("Fps : " + std::string(fps ? "On" : "Off"));
	}
	else
	{
		if (winFps != fps || winFullscreen != fullscreen
			|| winWidth != width || winHeight != height)
		{
			save(C_CONFIG("Core.cfg"));
			return (mod::restart);
		}
		return (mod::menu);
	}
	return (this->mymod);
}

void	Setting::save(const std::string & name)
{
	std::ofstream myfile;
	myfile.open(name);
	myfile << "Title:" + winTitle << std::endl;
	myfile << "Width:" + std::to_string(static_cast<int>(width)) << std::endl;
	myfile << "Height:" + std::to_string(static_cast<int>(height)) << std::endl;
	myfile << "Fullscreen:" + std::string(fullscreen ? "true" : "false") << std::endl;
	myfile << "Fps:" + std::string(fps ? "true" : "false") << std::endl;
	myfile.close();
}