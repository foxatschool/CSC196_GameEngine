#pragma once
#include "Framework/Component.h"

namespace shovel
{
	class AudioSource : public Component
	{
	public:
		std::string audioClipName; // Name of the audio clip to play
		
	public:
		CLASS_PROTOTYPE(AudioSource)
		// Inherited via Component
		void Update(float dt) override;
		void Play();
		
	};
}