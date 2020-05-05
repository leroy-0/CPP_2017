#include "Menu.h"
#include "Common.h"

Menu::Menu()
	: background(Sprite(R_SPRITE("background-menu.jpg")))
{
	this->background.setScale(winWidth / this->background.getTexture()->getSize().x,
		winHeight / this->background.getTexture()->getSize().y);

	this->choices[0] = std::unique_ptr<Text>(new Text(std::string(R_FONT("R-type.ttf"))));
	this->choices[0]->setString("Play");

	this->choices[1] = std::unique_ptr<Text>(new Text(std::string(R_FONT("R-type.ttf"))));
	this->choices[1]->setString("One vs One");

	this->choices[2] = std::unique_ptr<Text>(new Text(std::string(R_FONT("R-type.ttf"))));
	this->choices[2]->setString("Settings");

	this->choices[3] = std::unique_ptr<Text>(new Text(std::string(R_FONT("R-type.ttf"))));
	this->choices[3]->setString("Exit");

	this->sounds["ambient"] = std::unique_ptr<Sound>(new Sound(R_SOUND("menu.wav"), true));
	this->sounds["ambient"]->setLoop(true);

	this->sounds["change"] = std::unique_ptr<Sound>(new Sound(R_SOUND("change.wav"), false));

	this->sounds["select"] = std::unique_ptr<Sound>(new Sound(R_SOUND("select.wav"), false));

	this->mymod = mod::menu;
}

Menu::~Menu()
{

}

void	Menu::start()
{
	this->choices[0]->setPosition(winWidth / 2 - (this->choices[0]->getGlobalBounds().width / 2),
		winHeight * 0.2f - (this->choices[0]->getGlobalBounds().height / 2));
	this->choices[1]->setPosition(winWidth / 2 - (this->choices[1]->getGlobalBounds().width / 2),
		winHeight * 0.4f - (this->choices[1]->getGlobalBounds().height / 2));
	this->choices[2]->setPosition(winWidth / 2 - (this->choices[2]->getGlobalBounds().width / 2),
		winHeight * 0.6f - (this->choices[2]->getGlobalBounds().height / 2));
	this->choices[3]->setPosition(winWidth / 2 - (this->choices[3]->getGlobalBounds().width / 2),
		winHeight * 0.8f - (this->choices[3]->getGlobalBounds().height / 2));

	this->sounds["ambient"]->play();
	this->choosen = 0;
}

void	Menu::stop()
{
	this->sounds["ambient"]->stop();
}

void	Menu::setChoosen(int newChoosen)
{
	if (newChoosen >= static_cast<int>(choices.size()))
		this->choosen = 0;
	else if (newChoosen < 0)
		this->choosen = static_cast<int>(choices.size()) - 1;
	else
		this->choosen = newChoosen;
}

mod		Menu::getChoosen()
{
	if (this->choosen == 0)
		return (mod::connection);
	else if (this->choosen == 1)
		return (mod::play);
	else if (this->choosen == 2)
		return (mod::setting);
	return(mod::quit);
}

mod		Menu::events(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			this->sounds["change"]->play();
			this->setChoosen(this->choosen - 1);
		}
		else if (event.key.code == sf::Keyboard::Down)
		{
			this->sounds["change"]->play();
			this->setChoosen(this->choosen + 1);
		}
		else if (event.key.code == sf::Keyboard::Return)
		{
			this->sounds["ambient"]->stop();
			this->sounds["select"]->play();
			return (this->getChoosen());
		}
	}
	return (this->mymod);
}

void	Menu::exec()
{
	std::string		begin(M_CURSOR_L);
	std::string		end(M_CURSOR_R);
	int				choosenSize;

	for (int i = 0; i < static_cast<int>(this->choices.size()); i++)
	{
		if (this->choices[i]->getString().find(begin) != std::string::npos &&
			this->choices[i]->getString().find(end) != std::string::npos)
		{
			choosenSize = static_cast<int>(this->choices[i]->getString().getSize());
			this->choices[i]->setString(this->choices[i]->getString().substring(
				begin.size(), choosenSize - (begin.size() + end.size())));
			this->choices[i]->setPosition(winWidth / 2 -
				(this->choices[i]->getGlobalBounds().width / 2),
				this->choices[i]->getPosition().y);
		}
	}
	this->choices[this->choosen]->setString(begin +
		this->choices[this->choosen]->getString() + end);
	this->choices[this->choosen]->setPosition(winWidth / 2 -
		(this->choices[this->choosen]->getGlobalBounds().width / 2),
		this->choices[this->choosen]->getPosition().y);
}

void		Menu::display(sf::RenderWindow & window)
{
	window.draw(this->background);

	for (int i = 0; i < this->choices.size(); i++)
		window.draw(*this->choices[i]);
}

mod			Menu::run(sf::RenderWindow & window)
{
	this->exec();
	this->display(window);
	return (this->mymod);
}