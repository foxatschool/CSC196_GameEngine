#pragma once

#include <vector>
#include <memory>

namespace shovel {
	class Scene {
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr < class Actor >);
		
	private:
		std::vector < std::unique_ptr < class Actor >> m_actors;
	};
}