#include "Game.h"
#include "Menu.h"
#include "Connect.h"
#include "Play.h"
#include "Over.h"
#include "Multiplayer.h"
#include "Setting.h"

Game::Game()
	: fpsCounter(Text(R_FONT("R-type.ttf")))
{
	this->gameMod = mod::menu;
}

Game::~Game()
{
	
}

void	Game::start()
{
	this->core.load(C_CONFIG("Core.cfg"));

	if (winFps)
	{
		this->fpsCounter.setPosition(winWidth - (this->fpsCounter.getCharacterSize() * 3), winHeight * 0.025f);
		this->fpsCounter.setFillColor(sf::Color::Yellow);
	}

	this->scenes[mod::menu] = std::unique_ptr<IScene>(new Menu());
	this->scenes[mod::connection] = std::unique_ptr<IScene>(new Connect(conInfo));
	this->scenes[mod::multiplayer] = std::unique_ptr<IScene>(new Multiplayer(conInfo, this->core.getClock()));
	this->scenes[mod::play] = std::unique_ptr<IScene>(new Play());
	this->scenes[mod::setting] = std::unique_ptr<IScene>(new Setting());
	this->scenes[mod::over] = std::unique_ptr<IScene>(new Over());

	this->scenes[this->gameMod]->start();

	this->core.create();

	this->core.setFramerateLimit(120);
}

void	Game::stop()
{
	for (std::map<mod, std::unique_ptr<IScene>>::iterator itr = this->scenes.begin(); itr != this->scenes.end(); itr++)
	{
		itr->second.reset();
	}

	this->core.close();

	this->gameMod = this->gameMod == mod::restart ? mod::menu : mod::quit;
}

void	Game::events()
{
	sf::Event	event;
	mod			tempMod;

	while (this->core.pollEvent(event) &&
		this->gameMod != mod::quit && this->gameMod != mod::restart)
	{
		if (event.type == sf::Event::Closed)
			this->gameMod = mod::quit;
		else
		{
			tempMod = this->scenes[this->gameMod]->events(event);
			if (this->gameMod != tempMod)
			{
				if (tempMod != mod::quit && tempMod != mod::restart)
				{
					this->scenes[this->gameMod]->stop();
					this->scenes[tempMod]->start();
				}
				this->gameMod = tempMod;
			}
		}
	}
}

void	Game::exec()
{
	static sf::Time	elapsed = this->core.getClock().getElapsedTime();
	sf::Time		tmp;
	float			framerate;
	mod				tempMod;

	if (this->gameMod != mod::quit && this->gameMod != mod::restart)
	{
		tempMod = this->scenes[this->gameMod]->run(this->core);
		if (this->gameMod != tempMod)
		{
			if (tempMod != mod::quit && tempMod != mod::restart)
			{
				this->scenes[this->gameMod]->stop();
				this->scenes[tempMod]->start();
			}
			this->gameMod = tempMod;
		}
		if (winFps)
		{
			tmp = this->core.getClock().getElapsedTime();
			elapsed = tmp - elapsed;
			framerate = 1.0f / elapsed.asSeconds();
			this->fpsCounter.setString(std::to_string(static_cast<int>(framerate)));
			elapsed = this->core.getClock().getElapsedTime();
			this->core.draw(this->fpsCounter);
		}
		this->core.display();
	}
}

void	Game::run()
{
	while (this->gameMod != mod::quit)
	{
		this->start();

		while (this->gameMod != mod::restart &&
			this->gameMod != mod::quit)
		{

			this->events();
			this->exec();
		}

		this->stop();
	}
}