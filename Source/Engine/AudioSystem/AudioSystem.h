#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace shovel 
{
	class AudioSystem
	{
	public:
		AudioSystem() = default;

		bool Init();
		void ShutDown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "");
		bool PlaySound(const std::string& name, bool loop = false);
		bool PlaySound(class AudioClip& audioClip);

	private:
		static bool CheckFMODResult(FMOD_RESULT result);

	private:
		friend class AudioClip;

		FMOD::System* m_aSystem{nullptr};
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}