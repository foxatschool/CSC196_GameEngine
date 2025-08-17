#include "AudioClip.h"
#include "AudioSystem.h"

namespace shovel
{
	AudioClip::~AudioClip()
	{
		if (m_sound)
		{
			m_sound->release();
		}
	}

    bool AudioClip::Load(const std::string& filename, AudioSystem& audioSystem)
    {
        FMOD_RESULT result = audioSystem.m_aSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &m_sound);
        if (!AudioSystem::CheckFMODResult(result)) return false;
        return true;
    }

}
