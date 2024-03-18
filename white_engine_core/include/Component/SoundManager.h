#pragma once

#include "Component/IComponent.h"
#include <vector>

class Sound;

class SoundManager : public IComponent
{
public:

	SoundManager(GameObject& GameObject);
	~SoundManager();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	void addSound(std::string path, std::string musicName);
	void deleteSound(std::string musicName);
	void playSound(std::string musicName, bool looping);
	void stopSound(std::string musicName);

	static const std::string GetComponentName_Static();
	virtual const std::string GetComponentName() const override;

	std::vector<Sound*> getSoundList();

private:
	std::vector<Sound*> soundList;
};

