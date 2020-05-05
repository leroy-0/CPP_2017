#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.h"
#include "Sound.h"
#include "Player.h"
#include "Common.h"

class Over : public IScene
{
	public:
		Over();
		virtual ~Over();

		mod		run(sf::RenderWindow & window);
		mod		events(const sf::Event & event);
		void	start();
		void	stop();

	private:
		mod		exec();
		void	display(sf::RenderWindow & window);

	private:
		Sprite											background;
		std::map<std::string, std::unique_ptr<Sound>>	sounds;
};