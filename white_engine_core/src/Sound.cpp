#include "Sound.h"

Sound::Sound(std::string path, std::string musicName)
{
	if (!buffer.loadFromFile(path))
	{
		buffer.loadFromFile("../white_engine_core/Sounds/sound1.wav");
		soundPath = "../white_engine_core/Sounds/sound1.wav";
	}
	soundPath = path;

	if (musicName.empty())
		musicName = "default";
	name = musicName;

	sound.setBuffer(buffer);
}

Sound::~Sound()
{
	StopSound();
}

/* Play the sound one time */
void Sound::PlayOnce()
{
	sound.play();
}

/* Loop on the sound */
void Sound::PlayLoop()
{
	sound.setLoop(true);
	sound.play();
}

/* Stop looping on the sound */
void Sound::StopLoop()
{
	sound.setLoop(false);
}

/* Stop playing sound */
void Sound::StopSound()
{
	sound.stop();
}
