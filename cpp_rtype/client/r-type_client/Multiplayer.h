#pragma once

#include "IScene.h"
#include "IConnection.h"
#include "ConnectInfo.h"
#include "Control.h"
#include "Player.h"
#include "Sprite.h"
#include "Sound.h"
#include <memory>

class Multiplayer : public IScene
{
public:
	Multiplayer(ConnectInfo & _conInfo, const sf::Clock & _clock);
	virtual ~Multiplayer();

	mod		events(const sf::Event & event);
	mod		run(sf::RenderWindow & window);
	void	start();
	void	stop();
	mod		TCP();
	mod		UDP();

private:
	mod		analyseRFC();
	mod		exec();
	void	display(sf::RenderWindow & window);
	void	keys();

private:
	ConnectInfo	&									conInfo;
	Control											controller;

	const sf::Clock &								clock;
	sf::Time										lastTime;
	sf::Time										packetTime;

	Sprite											background_1;
	Sprite											background_2;

	std::map<int, std::unique_ptr<Player>>			players;
	std::map<std::string, std::unique_ptr<Sound>>	sounds;
	int												shootQuantity;
	int												iaQuantity;
	int												shootPos;
	int												iaPos;

	float											updateRatio;
	int												nbPackets;
};