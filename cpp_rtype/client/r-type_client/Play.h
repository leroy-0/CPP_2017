#pragma once

#include <SFML/Graphics.hpp>
#include "IScene.h"
#include "Player.h"
#include "Common.h"
#include <memory>

class Play : public IScene
{
	public:
		Play();
		virtual ~Play();
		
		mod		events(const sf::Event & event);
		mod		run(sf::RenderWindow & window);
		void	start();
		void	stop();

	private:
		mod		exec();
		void	display(sf::RenderWindow & window);
		void	keys();

	private:
		Sprite											background_1;
		Sprite											background_2;

		std::map<int, std::unique_ptr<Player>>			players;
		std::map<std::string, std::unique_ptr<Sound>>	sounds;
};