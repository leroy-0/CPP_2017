#pragma once

#include "Sprite.h"
#include "Text.h"
#include "Sound.h"
#include "Shoot.h"
#include <memory>

class Player : public Sprite
{
	public:
		Player(const std::string & pseudo, std::string & t_name, const std::string & id, bool ally);
		virtual ~Player();

	public:
		sf::Vector2f	getSpeed() const;
		int				getScore() const;
		std::string		getId() const;
		Text&			getScoreText();

		bool			isColliding(Sprite object) const;
		bool			isAlive() const;

		void			setId(const std::string & _id);
		bool			updateMove(const float updateRatio);
		void			moveShoots(std::map<int, std::unique_ptr<Player>> & players);
		void			setSpeed(const sf::Vector2f speed);
		void			setScore(int score);
		void			move(sf::Keyboard::Key dir, const float updateRatio);
		void			moveToPosition(float x, float y);
		void			shoot();
		void			die();

		void			display(sf::RenderWindow & win);

	private:
		std::map<std::string, std::unique_ptr<Sound>>	sounds;
		std::vector<std::unique_ptr<Shoot>>				shoots;
		
		sf::Vector2f									moveTo;

		bool											alive;
		bool											ally;

		sf::Vector2f									speed;

		std::string										pseudo;
		std::string										id;

		Text											t_score;
		int												score;
};