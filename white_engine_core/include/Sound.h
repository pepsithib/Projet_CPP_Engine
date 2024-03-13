#pragma once

#include <string>
#include <SFML/Audio.hpp>

class Sound
{
public:
	Sound(std::string path, std::string musicName);
	~Sound();

	void PlayOnce();
	void PlayLoop();
	void StopLoop();
	void StopSound();
	
	std::string name;
private:
	sf::SoundBuffer buffer;
	sf::Sound sound;
};

