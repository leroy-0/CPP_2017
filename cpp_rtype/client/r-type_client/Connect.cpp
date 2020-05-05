#include "Factory.h"
#include "Connect.h"
#include "Common.h"

Connect::Connect(ConnectInfo & _conInfo)
	: background(Sprite(R_SPRITE("Connect.png"))),
	conInfo(_conInfo)
{
	this->background.setScale(sf::Vector2f(winWidth / this->background.getGlobalBounds().width,
		winHeight / this->background.getGlobalBounds().height));

	this->choices[0] = std::unique_ptr<Text>(new Text(R_FONT("R-type.ttf")));
	this->choices[0]->setFillColor(sf::Color::White);

	this->choices[1] = std::unique_ptr<Text>(new Text(R_FONT("R-type.ttf")));
	this->choices[1]->setFillColor(sf::Color::White);

	this->choices[2] = std::unique_ptr<Text>(new Text(R_FONT("R-type.ttf")));
	this->choices[2]->setFillColor(sf::Color::White);

	this->choices[3] = std::unique_ptr<Text>(new Text(R_FONT("R-type.ttf")));
	this->choices[3]->setFillColor(sf::Color::White);

	this->choices[4] = std::unique_ptr<Text>(new Text(R_FONT("R-type.ttf")));
	this->choices[4]->setFillColor(sf::Color::Yellow);

	this->sounds["keystroke"] = std::unique_ptr<Sound>(new Sound(R_SOUND("keystroke.wav"), false));
	this->sounds["change"] = std::unique_ptr<Sound>(new Sound(R_SOUND("change.wav"), false));
	this->sounds["select"] = std::unique_ptr<Sound>(new Sound(R_SOUND("select.wav"), false));
	this->sounds["denied"] = std::unique_ptr<Sound>(new Sound(R_SOUND("denied.wav"), false));
}

Connect::~Connect()
{

}

void	Connect::start()
{
	this->conInfo.start();
	this->choosen = 0;
	this->roomChoosen = 0;

	this->choices[0]->setString("Ip Address :");
	this->choices[0]->setPosition(winWidth / 2 - (this->choices[0]->getGlobalBounds().width), winHeight * 0.2f);

	this->choices[1]->setString("Port :");
	this->choices[1]->setPosition(winWidth / 2 - (this->choices[1]->getGlobalBounds().width), winHeight * 0.3f);

	this->choices[2]->setString("Room Id :");
	this->choices[2]->setPosition(winWidth / 2 - (this->choices[2]->getGlobalBounds().width), winHeight * 0.4f);

	this->choices[3]->setString("Players :");
	this->choices[3]->setPosition(winWidth / 2 - (this->choices[3]->getGlobalBounds().width), winHeight * 0.5f);

	this->choices[4]->setString("Connect");
	this->choices[4]->setPosition(winWidth / 2 - (this->choices[4]->getGlobalBounds().width / 2), winHeight * 0.8f);
	this->choices[4]->setFillColor(sf::Color::Yellow);
}

void	Connect::stop()
{

}

mod	Connect::events(const sf::Event & event)
{
	if (event.type == sf::Event::TextEntered)
	{
		if (event.text.unicode < 128 &&
			(event.text.unicode >= 48 && event.text.unicode <= 57)
			|| event.text.unicode == 46)
		{
			this->sounds["keystroke"]->play();
			if (this->choosen == 0)
				this->ip += static_cast<char>(event.text.unicode);
			else if (this->choosen == 1)
				this->port += static_cast<char>(event.text.unicode);
		}
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::BackSpace)
		{
			this->sounds["keystroke"]->play();
			if (this->choosen == 0)
				this->ip = this->ip.substr(0, this->ip.size() - 1);
			else if (this->choosen == 1)
				this->port = this->port.substr(0, this->port.size() - 1);
		}
		else if (event.key.code == sf::Keyboard::Tab
			|| event.key.code == sf::Keyboard::Down)
		{
			this->sounds["change"]->play();
			this->choosen++;
		}
		else if (event.key.code == sf::Keyboard::Up)
		{
			this->sounds["change"]->play();
			this->choosen--;
		}
		else if (event.key.code == sf::Keyboard::Escape)
			return (mod::menu);
		else if (event.key.code == sf::Keyboard::Return)
		{
			if (this->choosen == 2)
			{
				this->roomChoosen++;
				if (this->roomChoosen >= static_cast<int>(this->conInfo.getRoomIds().size()))
					this->roomChoosen = 0;
			}
			else if (this->choosen == 4)
			{
				if (this->ip.empty() || this->port.empty())
					this->sounds["denied"]->play();
				else
					this->conInfo.checkStatus(this->ip, this->port);
			}
		}
	}
	return (mod::connection);
}

void	Connect::display(sf::RenderWindow & win)
{
	win.draw(this->background);

	for (int i = 0; i < this->choices.size(); i++)
		win.draw(*this->choices[i]);
}

mod	Connect::exec()
{
	std::string end("}");

	sf::Color	color;
	std::string	str;

	if (this->choosen > static_cast<int>(this->choices.size()) - 1)
		this->choosen = 0;
	else if (this->choosen < 0)
		this->choosen = static_cast<int>(this->choices.size()) - 1;

	color = sf::Color::Yellow;
	str = "Connect";
	if (!this->conInfo.isConnecting()["launch"] && this->conInfo.isConnecting()["connect"])
	{
		color = sf::Color::Blue;
		str = "Ready";
	}
	else if (this->conInfo.isConnecting()["launch"])
	{
		color = sf::Color::Green;
		str = "Launch";
	}

	this->choices[0]->setString("IP Address : " + this->ip + std::string(this->choosen == 0 ? end : ""));
	this->choices[1]->setString("Port : " + this->port + std::string(this->choosen == 1 ? end : ""));
	
	this->choices[2]->setString(std::string(this->choosen == 2 ? M_CURSOR_L : "") +
		"Room Id : " +
		std::to_string(this->roomChoosen) +
		std::string(this->choosen == 2 ? M_CURSOR_R : ""));
	this->choices[2]->setPosition(winWidth / 2 - (this->choices[2]->getGlobalBounds().width / 2),
		this->choices[2]->getPosition().y);

	this->choices[3]->setString(std::string(this->choosen == 3 ? M_CURSOR_L : "") +
		"Players : " +
		std::to_string(this->conInfo.getPlayerIds().size()) +
		std::string(this->choosen == 3 ? M_CURSOR_R : ""));
	this->choices[3]->setPosition(winWidth / 2 - (this->choices[3]->getGlobalBounds().width / 2),
		this->choices[3]->getPosition().y);

	this->choices[4]->setFillColor(color);
	this->choices[4]->setString(std::string(this->choosen == 4 ? M_CURSOR_L : "") + str +
		std::string(this->choosen == 4 ? M_CURSOR_R : ""));

	this->choices[4]->setPosition(winWidth / 2 - (this->choices[4]->getGlobalBounds().width / 2),
		this->choices[4]->getPosition().y);


	return (this->conInfo.run(this->ip, this->port));
}

mod		Connect::run(sf::RenderWindow & win)
{
	mod mymod;

	mymod = this->exec();
	this->display(win);
	return (mymod);
}