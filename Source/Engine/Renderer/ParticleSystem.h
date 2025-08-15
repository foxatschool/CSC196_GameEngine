#pragma once
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include <vector>

namespace shovel
{
	struct Particle
	{
		bool active{ false };

		float lifetime{ 1 };

		vec2 position;
		vec2 velocity;

		vec3 color;
	};

	class ParticleSystem
	{
	public:
		ParticleSystem() = default;

		bool Initialize(int poolSize = 1000);
		void ShutDown();

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddParticle(const Particle& particle);

	private:
		Particle* GetFreeParticle();
	private:
		std::vector<Particle> m_particles;
	};
}