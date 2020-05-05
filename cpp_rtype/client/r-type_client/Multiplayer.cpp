#include "Multiplayer.h"

Multiplayer::Multiplayer(ConnectInfo & _conInfo, const sf::Clock & _clock)
	: conInfo(_conInfo), clock(_clock), background_1(Sprite(R_SPRITE("background-menu.jpg"))),
	background_2(Sprite(R_SPRITE("background-menu.jpg")))
{
	this->background_1.setScale(sf::Vector2f(winWidth / this->background_1.getGlobalBounds().width,
		winHeight / this->background_1.getGlobalBounds().height));

	this->background_2.setScale(sf::Vector2f(winWidth / this->background_2.getGlobalBounds().width,
		winHeight / this->background_2.getGlobalBounds().height));
	this->background_2.setPosition(sf::Vector2f(winWidth, 0));

	this->sounds["ambient"] = std::unique_ptr<Sound>(new Sound(R_SOUND("game.wav"), true));
	this->sounds["ambient"]->setLoop(true);
}

Multiplayer::~Multiplayer()
{

}

void	Multiplayer::start()
{
	int		j = 0;

	this->nbPackets = 0;
	this->shootQuantity = 50;
	this->iaQuantity = 10;

	this->iaPos = static_cast<int>(this->conInfo.getPlayerIds().size());
	this->shootPos = this->iaPos + this->iaQuantity;

	this->sounds["ambient"]->play();
	this->background_1.setPosition(0, 0);
	this->background_2.setPosition(winWidth, 0);

	this->players[j] = std::unique_ptr<Player>(new Player("Player_" + this->conInfo.getMyPlayerId(),
		std::string(R_SPRITE("ship-" + std::to_string(j + 1) + std::string(".png"))), this->conInfo.getMyPlayerId(), true));
	j++;

	for (int i = 0; i < this->conInfo.getPlayerIds().size(); i++)
	{
		if (this->conInfo.getPlayerIds()[i] != this->conInfo.getMyPlayerId())
		{
			this->players[j] = std::unique_ptr<Player>(new Player("Player_" + this->conInfo.getPlayerIds()[i],
				std::string(R_SPRITE("ship-" + std::to_string(j + 1) + std::string(".png"))), this->conInfo.getPlayerIds()[i], true));
			j++;
		}
	}

	for (short i = this->iaPos; i < this->iaPos + this->iaQuantity; i++)
	{
		this->players[i] = std::unique_ptr<Player>(new Player("Enemy",
			std::string(R_SPRITE("Enemy.png")), std::string(""), true));
		this->players[i]->setPosition(-100, 0);
		this->players[i]->moveToPosition(-100, 0);
	}

	for (short i = this->shootPos; i < this->shootPos + this->shootQuantity; i++)
	{
		this->players[i] = std::unique_ptr<Player>(new Player("Shoot",
			std::string(R_SPRITE("shoot.png")), std::string(""), true));
		this->players[i]->setPosition(-100, 0);
		this->players[i]->moveToPosition(-100, 0);
	}

	this->lastTime = this->clock.getElapsedTime();
	this->packetTime = this->lastTime;
}

void	Multiplayer::stop()
{
	this->sounds["ambient"]->stop();
	this->players.clear();
	this->conInfo.stop();
}

mod		Multiplayer::events(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == this->controller.getKey("Leave"))
		{
//			this->udpConnection->Send("501 " + this->players[0]->getId());
			return (mod::menu);
		}
		if (event.key.code == this->controller.getKey("Shoot"))
		{
			std::cout << "shoot" << std::endl;
			this->conInfo.getUdp()->Send("408 " + this->players[0]->getId());
			this->nbPackets++;
		}
	}
	return (mod::multiplayer);
}

void	Multiplayer::keys()
{
	if (!this->players[0]->updateMove(this->updateRatio))
		return;

	if (sf::Keyboard::isKeyPressed(this->controller.getKey("Up")))
	{
		this->conInfo.getUdp()->Send("401 " + this->players[0]->getId());
		this->nbPackets++;
	}
	if (sf::Keyboard::isKeyPressed(this->controller.getKey("Down")))
	{
		this->conInfo.getUdp()->Send("402 " + this->players[0]->getId());
		this->nbPackets++;
	}
	if (sf::Keyboard::isKeyPressed(this->controller.getKey("Left")))
	{
		this->conInfo.getUdp()->Send("403 " + this->players[0]->getId());
		this->nbPackets++;
	}
	if (sf::Keyboard::isKeyPressed(this->controller.getKey("Right")))
	{
		this->conInfo.getUdp()->Send("404 " + this->players[0]->getId());
		this->nbPackets++;
	}
}

mod	Multiplayer::analyseRFC()
{
	if (this->conInfo.getTcp()->HasMessages())
		this->TCP();
	if (this->conInfo.getUdp()->HasMessages())
		this->UDP();
	return (mod::multiplayer);
}

mod Multiplayer::TCP()
{
	std::vector<std::string>	words;
	std::vector<std::string>	words2;
	std::string					str;
	std::string					tmp;
	int							code;

	str = this->conInfo.getTcp()->GetOneMessage();
	words = this->conInfo.split(this->conInfo.split(str, '\n')[0], ' ');
	if (words.size() > 0)
	{
		code = std::stoi(words[0]);
		if (words.size() > 1)
			words = this->conInfo.split(words[1], ':');
		else
			words.clear();

		switch (code)
		{
		case 406:
			for (short i = 0; i < words.size(); i++)
			{
				words2 = this->conInfo.split(words[i], ',');
				if (words2.size() >= 2)
				{
					for (short i = 0; i < this->players.size(); i++)
					{
						if (this->players[i]->getId() == words2[0])
						{
							this->players[i]->setPosition(std::stof(words2[1]), std::stof(words2[2]));
							this->players[i]->moveToPosition(std::stof(words2[1]), std::stof(words2[2]));
							break;
						}
					}
				}
			}
			break;
		}
	}
}

mod Multiplayer::UDP()
{
	std::vector<int>			uuids;
	bool						first = true;
	std::vector<std::string>	words;
	std::vector<std::string>	words2;
	std::string					str;
	std::string					tmp;
	int							code;

	str = this->conInfo.getUdp()->GetOneMessage();
	words = this->conInfo.split(this->conInfo.split(str, '\n')[0], ' ');

	if (words.size() > 0)
	{
		code = std::stoi(words[0]);
		if (words.size() > 1)
			words = this->conInfo.split(words[1], ':');
		else
			words.clear();

		switch (code)
		{
		case 407:
			for (short i = 0; i < words.size(); i++)
			{
				words2 = this->conInfo.split(words[i], ',');
				if (words2.size() >= 2)
				{
					bool find = false;

					for (short i = 0; i < this->players.size(); i++)
					{
						if (first)
							uuids.push_back(false);
						if (this->players[i]->getId() == words2[0])
						{
							this->players[i]->setPosition(std::stof(words2[1]), std::stof(words2[2]));
							this->players[i]->moveToPosition(std::stof(words2[1]), std::stof(words2[2]));
							find = true;
							uuids.at(i) = true;
							if (!first)
								break;
						}
					}
					first = false;
					if (!find)
					{
						if ("enemy" == words2[3])
						{
							uuids.at(i) = true;
							int pos = -1;
							for (short i = 0; i < this->players.size(); i++)
							{
								if (this->players[i]->getId().empty()
									&& i >= this->iaPos && i < this->shootPos)
								{
									pos = i;
									break;
								}
							}
							if (pos != -1)
							{
								this->players[pos]->setId(words2[0]);
								this->players[pos]->setPosition(std::stof(words2[1]), std::stof(words2[2]));
								this->players[pos]->moveToPosition(std::stof(words2[1]), std::stof(words2[2]));
							}
						}
						else if ("projectile" == words2[3])
						{
							uuids.at(i) = true;
							int pos = -1;
							for (short i = 0; i < this->players.size(); i++)
							{
								if (this->players[i]->getId().empty()
									&& i >= this->shootPos)
								{
									pos = i;
									break;
								}
							}
							if (pos != -1)
							{
								this->players[pos]->setId(words2[0]);
								this->players[pos]->setPosition(std::stof(words2[1]), std::stof(words2[2]));
								this->players[pos]->moveToPosition(std::stof(words2[1]), std::stof(words2[2]));
							}
						}
					}
				}
			}
			for (short i = 0; i < uuids.size(); i++)
			{
				if (uuids.at(i) == false && !this->players[i]->getId().empty())
				{
					this->players[i]->setPosition(-100, 0);
					this->players[i]->setId(std::string(""));
				}
			}
			break;
		}
	}
}

mod	Multiplayer::exec()
{
	this->background_1.setPosition(this->background_1.getPosition().x - 1, this->background_1.getPosition().y);
	this->background_2.setPosition(this->background_2.getPosition().x - 1, this->background_2.getPosition().y);

	if (this->background_1.getPosition().x + this->background_1.getGlobalBounds().width <= 0)
	{
		this->background_1.setPosition(0, this->background_1.getPosition().y);
		this->background_2.setPosition(winWidth, this->background_2.getPosition().y);
	}

	for (int i = 0; i < this->players.size(); i++)
	{
		if (!this->players[i]->getId().empty())
			this->players[i]->updateMove(this->updateRatio);
	}

	return (this->analyseRFC());
}

void	Multiplayer::display(sf::RenderWindow & window)
{
	window.draw(this->background_1);
	window.draw(this->background_2);

	for (int i = 0; i < this->players.size(); i++)
	{
		if (this->players[i]->getId() == this->conInfo.getMyPlayerId())
			window.draw(this->players[i]->getScoreText());
		if (!this->players[i]->getId().empty())
			this->players[i]->display(window);
	}
}

mod		Multiplayer::run(sf::RenderWindow & window)
{
	mod				mod;
	sf::Time		tmp;

	tmp = this->clock.getElapsedTime();
	this->updateRatio = tmp.asSeconds() - this->lastTime.asSeconds();
	if (tmp.asMilliseconds() - this->packetTime.asMilliseconds() > 40)
	{
		this->nbPackets = 0;
		this->packetTime = this->clock.getElapsedTime();
	}
	if (tmp.asMilliseconds() - this->packetTime.asMilliseconds() < 40
		&& this->nbPackets < 2)
	{
		this->keys();
	}
	mod = this->exec();
	this->display(window);
	this->lastTime = tmp;
	return (mod);
}