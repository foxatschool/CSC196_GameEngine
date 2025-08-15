#include "ParticleSystem.h"
#include "Renderer.h"

namespace shovel
{

    bool ParticleSystem::Initialize(int poolSize)
    {
        //reserve particles in pool
		m_particles.resize(poolSize); // Reserve space for 1000 particles

        return true;
    }

    void ParticleSystem::ShutDown()
    {
		m_particles.clear(); // Clear the particle pool
    }

    void ParticleSystem::Update(float dt)
    {
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				particle.lifetime -= dt;
				particle.active = particle.lifetime > 0;
				particle.position += particle.velocity * dt;
                
			}
		}
    }

    void ParticleSystem::Draw(Renderer& renderer)
    {
		for (auto& particle : m_particles)
		{
			if (particle.active)
			{
				// Set the color for the particle
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				// Draw the particle using its position and color
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
    }
    void ParticleSystem::AddParticle(const Particle& particle)
    {
		Particle* freeParticle = GetFreeParticle();
		if (freeParticle)
		{
			*freeParticle = particle; // Copy the particle data to the free particle
			freeParticle->active = true;
			
		}
    }
    Particle* ParticleSystem::GetFreeParticle()
    {
		for (auto& particle : m_particles)
		{
			if (!particle.active)
			{
				return &particle;
			}
		}

        return nullptr;
    }
}
