#include "Sound.h"

Sound::Sound(const std::string & name, bool _longmusic)
{
	this->longmusic = _longmusic;

	if (_longmusic)
		this->music.openFromFile(name);
	else
	{
		if (this->buffer.loadFromFile(name))
			this->sound.setBuffer(buffer);
	}
}

Sound::~Sound()
{
}

void	Sound::play()
{
	if (this->longmusic)
		this->music.play();
	else
		this->sound.play();
}

void	Sound::stop()
{
	if (this->longmusic)
		this->music.stop();
	else
		this->sound.stop();
}

void	Sound::setLoop(bool loop)
{
	if (this->longmusic)
		this->music.setLoop(loop);
	else
		this->sound.setLoop(loop);
}

sf::SoundSource::Status	Sound::getStatus() const
{
	if (this->longmusic)
		return (this->music.getStatus());
	return (this->sound.getStatus());
}
