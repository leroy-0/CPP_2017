#include "Player.h"
#include "Common.h"

Player::Player(const std::string & pseudo, std::string & t_name, const std::string & id, bool _ally)
	: Sprite(t_name), t_score(Text(R_FONT("R-type.ttf")))
{
	this->ally = _ally;
	this->pseudo = pseudo;
	this->alive = true;
	this->id = id;

	this->setPosition(0, 0);
	this->setSpeed(sf::Vector2f(D_SPEED_X, D_SPEED_Y));
	this->setScore(0);

	this->t_score.setPosition(winWidth * 0.75f, winHeight * 0.025f);

	this->sounds["shoot"] = std::unique_ptr<Sound>(new Sound(R_SOUND("shoot.wav"), false));
	this->sounds["death"] = std::unique_ptr<Sound>(new Sound(R_SOUND("death.wav"), false));

	moveTo.x = 0;
	moveTo.y = 0;
}

Player::~Player()
{

}

void		Player::setId(const std::string & _id)
{
	this->id = _id;
}

bool		Player::updateMove(const float updateRatio)
{
	bool	isDone = true;

	if (moveTo.x < getPosition().x)
	{
		this->move(sf::Keyboard::Left, updateRatio);
		isDone = false;
	}
	if (moveTo.x > getPosition().x)
	{
		this->move(sf::Keyboard::Right, updateRatio);
		isDone = false;
	}
	if (moveTo.y < getPosition().y)
	{
		this->move(sf::Keyboard::Up, updateRatio);
		isDone = false;
	}
	if (moveTo.y > getPosition().y)
	{
		this->move(sf::Keyboard::Down, updateRatio);
		isDone = true;
	}
	return (isDone);
}

void			Player::moveToPosition(const float x, const float y)
{
	moveTo.x = x;
	moveTo.y = y;
}

std::string		Player::getId() const
{
	return (this->id);
}

Text&	Player::getScoreText()
{
	return (this->t_score);
}

int		Player::getScore() const
{
	return (score);
}

sf::Vector2f	Player::getSpeed() const
{
	return (this->speed);
}

bool	Player::isColliding(Sprite object) const
{
	return (getGlobalBounds().intersects(object.getGlobalBounds()));
}

bool	Player::isAlive() const
{
	return (this->alive);
}

void	Player::setScore(int score)
{
	this->score = score;
	this->t_score.setString(std::to_string(this->score));
}

void	Player::setSpeed(const sf::Vector2f speed)
{
	this->speed = speed;
}

void	Player::move(sf::Keyboard::Key dir, const float updateRatio)
{
	sf::Vector2f	pos(getPosition().x, getPosition().y);

	if (dir == sf::Keyboard::Left)
		pos.x -= updateRatio * this->speed.x;
	else if (dir == sf::Keyboard::Right)
		pos.x += updateRatio * this->speed.x;
	else if (dir == sf::Keyboard::Up)
		pos.y -= updateRatio * this->speed.y;
	else if (dir == sf::Keyboard::Down)
		pos.y += updateRatio * this->speed.y;

	if (pos.x + this->getGlobalBounds().width <= winWidth &&
		pos.x >= 0 &&
		pos.y + this->getGlobalBounds().height <= winHeight &&
		pos.y >= 0)
		setPosition(pos);
}

void		Player::shoot()
{
	this->sounds["shoot"]->play();
	this->shoots.push_back(std::unique_ptr<Shoot>(new Shoot(R_SPRITE("shoot.png"))));
	this->shoots.back()->setPosition(getPosition().x, getPosition().y + (getGlobalBounds().height / 2));
}

void	Player::moveShoots(std::map<int, std::unique_ptr<Player>> & players)
{
	for (auto it = this->shoots.begin(); it < this->shoots.end();)
	{
		if (this->ally)
			(*it)->setPosition((*it)->getPosition().x + S_SPEED, (*it)->getPosition().y);
		else
			(*it)->setPosition((*it)->getPosition().x - S_SPEED, (*it)->getPosition().y);

		for (int i = 0; i < players.size(); i++)
		{
			if (players[i]->id != this->id)
			{
				if (players[i]->isColliding(*(*it)))
				{
					it = this->shoots.erase(it);
					players[i]->die();
					players[i]->setPosition(winWidth / 2, winHeight / 2);
					this->setScore(this->getScore() + 1);
					break;
				}
			}
		}

		if ((*it)->getPosition().x > winWidth || (*it)->getPosition().x < 0)
			it = this->shoots.erase(it);
		else
			it++;
	}
}

void	Player::die()
{
	this->sounds["death"]->play();
	this->alive = false;
}

void	Player::display(sf::RenderWindow & win)
{
	for (auto it = this->shoots.begin(); it < this->shoots.end(); it++)
		win.draw(*(*it));
	win.draw(*this);
}
