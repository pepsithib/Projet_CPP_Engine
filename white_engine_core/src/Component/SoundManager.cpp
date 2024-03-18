#include "../Component/SoundManager.h"
#include "Sound.h"

SoundManager::SoundManager(GameObject& GameObject) : IComponent(GameObject)
{
}

SoundManager::~SoundManager()
{
	for (Sound* i : soundList)
	{
		delete i;
	}
}

void SoundManager::Start()
{
}

void SoundManager::Update(float deltaTime)
{
}

void SoundManager::Destroy()
{
}

void SoundManager::addSound(std::string path, std::string musicName)
{
	soundList.push_back(new Sound(path, musicName));
}

void SoundManager::deleteSound(std::string musicName)
{
	for (int i = 0; i < soundList.size(); i++)
	{
		if (soundList[i]->name == musicName)
		{
			delete soundList[i];
			soundList.erase(soundList.begin()+i);
			break;
		}
	}
}

void SoundManager::playSound(std::string musicName, bool looping)
{
	for (Sound* i : soundList)
	{
		if (i->name == musicName)
		{
			if (looping)
				i->PlayLoop();
			else
			{
				i->PlayOnce();
			}
		}
	}
}

void SoundManager::stopSound(std::string musicName)
{
	for (Sound* i : soundList)
	{
		if (i->name == musicName)
		{
			i->StopLoop();
			break;
		}
	}
}

const std::string SoundManager::GetComponentName_Static()
{
	return "SoundManager";
}

const std::string SoundManager::GetComponentName() const
{
	return GetComponentName_Static();
}

std::vector<Sound*> SoundManager::getSoundList()
{
	return soundList;
}

