#include "AudioManagement.h"

AudioManagement::AudioManagement()
{
	loadAudioResources();
}

void AudioManagement::loadAudioResources()
{
	if (!mainMusic.openFromFile("../resources/Audio/victory.wav"))
	{
		std::cout << "Error loading main music" << std::endl;
	}
	if (!coinSoundBuffer.loadFromFile("../resources/Audio/coin.wav"))
	{
		std::cout << "Error loading coin sound" << std::endl;
	}
	if (!jumpSoundBuffer.loadFromFile("../resources/Audio/jump.wav"))
	{
		std::cout << "Error loading jump sound" << std::endl;
	}
	if (!destroyBlockSoundBuffer.loadFromFile("../resources/Audio/rock-destroy.wav"))
	{
		std::cout << "Error loading destroy block sound" << std::endl;
	}
	if (!monsterHitSoundBuffer.loadFromFile("../resources/Audio/dead.wav"))
	{
		std::cout << "Error loading monster hit sound" << std::endl;
	}
	if (!monsterRoarSoundBuffer.loadFromFile("../resources/Audio/monster-roar.wav"))
	{
		std::cout << "Error loading monster roar sound" << std::endl;
	}

	coinSound.setBuffer(coinSoundBuffer);
	jumpSound.setBuffer(jumpSoundBuffer);
	destroyBlockSound.setBuffer(destroyBlockSoundBuffer);
	monsterHitSound.setBuffer(monsterHitSoundBuffer);
	monsterRoarSound.setBuffer(monsterRoarSoundBuffer);
}

void AudioManagement::playMainMusic()
{
	//set volume
	mainMusic.setVolume(20);
	mainMusic.setLoop(true);
	if (mOnSound) {
		mainMusic.play();
	}
}

void AudioManagement::playCoinSound()
{
	coinSound.setVolume(80);
	if (mOnSound) {
		coinSound.play();
	}
}

void AudioManagement::playJumpSound()
{
	jumpSound.play();
}

void AudioManagement::playDestroyBlockSound()
{
	destroyBlockSound.setVolume(40);
	if (mOnSound) {
		destroyBlockSound.play();
	}
}

void AudioManagement::stopMainMusic()
{
	mainMusic.stop();
}

void AudioManagement::playMonsterHitSound()
{
	monsterHitSound.setVolume(20);
	if (mOnSound) {
		monsterHitSound.play();
	}
}

void AudioManagement::switchOnOff()
{
	if (mOnSound) {
		mOnSound = false;
	}
	else {
		mOnSound = true;
	}
}

bool AudioManagement::isOnSound() const
{
	return mOnSound;
}

void AudioManagement::playMonsterRoarSound()
{
	monsterRoarSound.setVolume(40);
	if (mOnSound) {
		monsterRoarSound.play();
	}
}