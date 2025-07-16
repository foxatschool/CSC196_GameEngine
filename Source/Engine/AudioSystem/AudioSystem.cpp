#include "AudioSystem.h"
#include "../Core/StringHelper.h"

#include <fmod_errors.h>
#include <iostream>

namespace shovel
{
	bool AudioSystem::CheckFMODResult(FMOD_RESULT result)
	{
		if (result != FMOD_OK)
		{
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}

		return true;
	}

	bool AudioSystem::Init()
	{
		FMOD_RESULT result = FMOD::System_Create(&m_aSystem);
		if (!CheckFMODResult(result)) return false;

		FMOD::System_Create(&m_aSystem);
		void* extradriverdata = nullptr;
		result = m_aSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result)) return false;

		return true;
	}
	/// <summary>
	/// Attempts to add a new sound to the audio system.
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="name"></param>
	/// <returns></returns>
	bool AudioSystem::AddSound(const std::string& filename, const std::string& name)
	{
		std::string key = (name.empty()) ? filename : name;
		// Convert to lowercase
		key = shovel::toLower(key);

		// check if dey exists in sounds map
		if (m_sounds.find(key) != m_sounds.end())
		{
			std::cerr << "Audio System : Name Alerady exists " << key << std::endl;
			return false;
		}
		
		// Create Sound
		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_aSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) return false;
		//audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
		//sounds.push_back(sound);

		//insert sound into the map
		m_sounds[key] = sound;

		return true;
	}
	bool AudioSystem::PlaySound(const std::string& name, bool loop)
	{
		std::string key = name;

		// Convert to lowercase
		key = shovel::toLower(key);

		if (m_sounds.find(name) == m_sounds.end())
		{
			std::cerr << "Audio System : Name doesn't exist " << key << std::endl;
			return false;
		}

		FMOD_RESULT result = m_aSystem->playSound(m_sounds[name], 0, false, nullptr);
		if (!CheckFMODResult(result)) return false;
		return true;
	}

	void AudioSystem::ShutDown()
	{
		CheckFMODResult(m_aSystem->release());

	}

	void AudioSystem::Update()
	{
		CheckFMODResult(m_aSystem->update());
	}
}