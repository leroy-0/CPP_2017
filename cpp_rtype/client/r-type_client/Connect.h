#pragma once

#include "IConnection.h"
#include "IScene.h"
#include "Sprite.h"
#include "Text.h"
#include "Sound.h"
#include "ConnectInfo.h"

class Connect : public IScene
{
public:
	Connect(ConnectInfo & conInfo);
	virtual ~Connect();

	mod							run(sf::RenderWindow & win);
	mod							events(const sf::Event & event);
	void						start();
	void						stop();

private:
	mod							exec();
	void						display(sf::RenderWindow & win);

private:
	Sprite											background;
	ConnectInfo&									conInfo;

	std::vector<std::string>						player_ids;
	bool											connected;
	bool											ready;
	bool											launch;

	std::map<int, std::unique_ptr<Text>>			choices;
	std::map<std::string, std::unique_ptr<Sound>>	sounds;
	
	std::string										ip;
	std::string										port;

	int												choosen;
	int												roomChoosen;
};