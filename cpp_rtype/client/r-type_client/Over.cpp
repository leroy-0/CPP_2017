#include "Over.h"

Over::Over()
	: background(Sprite(R_SPRITE("die.png")))
{
	this->background.setScale(sf::Vector2f(winWidth / this->background.getGlobalBounds().width,
		winHeight / this->background.getGlobalBounds().height));

	this->sounds["ambient"] = std::unique_ptr<Sound>(new Sound(R_SOUND("death.wav"), false));
}

Over::~Over()
{

}

void	Over::start()
{
	this->sounds["ambient"]->play();
}

void	Over::stop()
{
	this->sounds["ambient"]->stop();
}

mod		Over::exec()
{
	if (this->sounds["ambient"]->getStatus() == sf::SoundSource::Status::Stopped
		|| this->sounds["ambient"]->getStatus() == sf::SoundSource::Status::Paused)
		return (mod::menu);
	return (mod::over);
}

void	Over::display(sf::RenderWindow & window)
{
	window.draw(this->background);
}

mod		Over::events(const sf::Event & event)
{
	return (mod::over);
}

mod		Over::run(sf::RenderWindow & window)
{
	mod mod;

	mod = this->exec();
	this->display(window);
	return (mod);
}
