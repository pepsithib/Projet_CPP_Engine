#pragma once

#include "Component/IComponent.h"
#include <vector>

class Sound;

class SoundManager : public IComponent
{
public:

	SoundManager(GameObject& GameObject);
	~SoundManager();

	/* Inherit Function */
	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	/* Add Sound to the list */
	void addSound(std::string path, std::string musicName);

	/* Delete a sound by name */
	void deleteSound(std::string musicName);

	/* Play a sound */
	void playSound(std::string musicName, bool looping);

	/* Stop a sound if it looping */
	void stopSound(std::string musicName);

	static const std::string GetComponentName_Static();
	virtual const std::string GetComponentName() const override;

	std::vector<Sound*> getSoundList();

private:
	std::vector<Sound*> soundList;
};

