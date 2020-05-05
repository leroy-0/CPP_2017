#pragma once

#include "IScene.h"
#include "Sound.h"
#include "Player.h"
#include "Text.h"
#include <memory>

class Menu : public IScene
{
	public:
		Menu();
		virtual ~Menu();

		mod		run(sf::RenderWindow & window);
		mod		events(const sf::Event & event);
		void	start();
		void	stop();

	protected:
		void		exec();
		void		display(sf::RenderWindow & window);

		void		setChoosen(int tempChoosen);
		virtual mod	getChoosen();

		mod			mymod;

	protected:
		Sprite											background;

		std::map<std::string, std::unique_ptr<Sound>>	sounds;
		std::map<int, std::unique_ptr<Text>>			choices;

		int												choosen;
};