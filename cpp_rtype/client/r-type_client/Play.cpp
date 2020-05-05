#include "Play.h"
#include "Common.h"

Play::Play()
	: background_1(Sprite(R_SPRITE("background-menu.jpg"))),
	background_2(Sprite(R_SPRITE("background-menu.jpg")))
{
	this->background_1.setScale(sf::Vector2f(winWidth / this->background_1.getGlobalBounds().width,
		winHeight / this->background_1.getGlobalBounds().height));

	this->background_2.setScale(sf::Vector2f(winWidth / this->background_2.getGlobalBounds().width,
		winHeight / this->background_2.getGlobalBounds().height));
	this->background_2.setPosition(sf::Vector2f(winWidth, 0));

	this->sounds["ambient"] = std::unique_ptr<Sound>(new Sound(R_SOUND("onevsone.wav"), true));
	this->sounds["ambient"]->setLoop(true);

	this->players[0] = std::unique_ptr<Player>(new Player(std::string("Leader"), std::string(R_SPRITE("c_sad_pepe.png")), "1", true));
	this->players[0]->setPosition(10, winHeight / 2);
	this->players[0]->getScoreText().setPosition(winWidth * 0.25f, winHeight * 0.025f);
	this->players[0]->getScoreText().setFillColor(sf::Color::Blue);

	this->players[1] = std::unique_ptr<Player>(new Player(std::string("Noob"), std::string(R_SPRITE("c_sad_pepe.png")), "2", false));
	this->players[1]->setPosition(winWidth - this->players[1]->getGlobalBounds().width - 10, winHeight / 2);
	this->players[1]->getScoreText().setFillColor(sf::Color::Red);
}

Play::~Play()
{

}

void	Play::start()
{
	this->sounds["ambient"]->play();
	this->background_1.setPosition(0, 0);
	this->background_2.setPosition(winWidth, 0);
	this->players[0]->setPosition(0, winHeight / 2);
}

void	Play::stop()
{
	this->sounds["ambient"]->stop();
}

mod		Play::events(const sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
			return (mod::menu);
		if (event.key.code == sf::Keyboard::Return)
			this->players[1]->shoot();
		if (event.key.code == sf::Keyboard::Space)
			this->players[0]->shoot();
	}
	return (mod::play);
}

mod	Play::exec()
{
	this->background_1.setPosition(this->background_1.getPosition().x - 10, this->background_1.getPosition().y);
	this->background_2.setPosition(this->background_2.getPosition().x - 10, this->background_2.getPosition().y);

	if (this->background_1.getPosition().x + this->background_1.getGlobalBounds().width <= 0)
	{
		this->background_1.setPosition(0, this->background_1.getPosition().y);
		this->background_2.setPosition(winWidth, this->background_2.getPosition().y);
	}

	for (int i = 0; i < this->players.size(); i++)
		this->players[i]->moveShoots(this->players);

	return (mod::play);
}

void	Play::display(sf::RenderWindow & window)
{
	window.draw(this->background_1);
	window.draw(this->background_2);

	for (int i = 0; i < this->players.size(); i++)
	{
		this->players[i]->display(window);
	}
}

void	Play::keys()
{
	float speed = 60;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->players[1]->move(sf::Keyboard::Left, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->players[1]->move(sf::Keyboard::Right, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->players[1]->move(sf::Keyboard::Up, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->players[1]->move(sf::Keyboard::Down, speed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		this->players[0]->move(sf::Keyboard::Left, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->players[0]->move(sf::Keyboard::Right, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		this->players[0]->move(sf::Keyboard::Up, speed);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->players[0]->move(sf::Keyboard::Down, speed);
}

mod		Play::run(sf::RenderWindow & window)
{
	mod	mod;

	this->keys();
	mod = this->exec();
	this->display(window);
	return (mod);
}