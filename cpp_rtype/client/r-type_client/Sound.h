#pragma once

#include <SFML/Audio.hpp>

class Sound
{
	public:
		Sound(const std::string & name, bool longmusic);
		virtual ~Sound();

		void					play();
		void					stop();
		void					setLoop(bool loop);
		sf::SoundSource::Status	getStatus() const;

	private:
		sf::Sound			sound;
		sf::Music			music;
		sf::SoundBuffer		buffer;
		bool				longmusic;
};