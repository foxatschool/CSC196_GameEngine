#include "EnginePCH.h"
#include "AudioSource.h"
#include "AudioSystem/AudioClip.h"
#include "AudioSystem/AudioSystem.h"
#include "Engine.h"

namespace shovel
{
	void AudioSource::Update(float dt)
	{

	}

	void AudioSource::Play()
	{
		auto audioClip = Resources().Get<AudioClip>(audioClipName, GetEngine().GetAudio());
		if (audioClip)
		{
			GetEngine().GetAudio().PlaySound(audioClip);
		}
	}
}
