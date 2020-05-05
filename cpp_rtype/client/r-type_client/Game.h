#pragma once

#include "IScene.h"
#include "ConnectInfo.h"
#include "Common.h"
#include "Core.h"
#include "Text.h"

#include <memory>

class Game
{
	public:
		Game();
		virtual ~Game();

		void	run();

	private:
		void	start();
		void	events();
		void	exec();
		void	stop();

	private:
		std::map<mod, std::unique_ptr<IScene>>	scenes;
		ConnectInfo								conInfo;
		Core									core;
		Text									fpsCounter;

		mod										gameMod;
};