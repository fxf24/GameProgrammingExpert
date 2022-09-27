#include "framework.h"

Sound::Sound()
{
	
}

Sound::~Sound()
{
	for (auto iter = SoundList.begin(); iter != SoundList.end(); iter++)
	{
		iter->second->channel->stop();

	}
}

bool Sound::AddSound(string File, string key, bool loop)
{
	SoundNode* temp;
	if (loop)
	{
		temp->sound->setMode();
	}
	return false;
}

bool Sound::DeleteSound(string Key)
{
	return false;
}

void Sound::Play(string Key)
{
	auto iter = SoundList.find(Key);
}

void Sound::Stop(string Key)
{
}

void Sound::Pause(string Key)
{
}

void Sound::Resume(string Key)
{
}

void Sound::SetVolume(string Key, float scale)
{
	auto iter = SoundList.find(Key);

	if (iter != SoundList.end())
	{
		iter->second->volume = scale;

	}
}

void Sound::SetMasterVolume()
{
}

void Sound::Update()
{
}
