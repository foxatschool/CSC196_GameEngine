#pragma once
#include "RendererComponent.h"

namespace shovel
{
	class MeshRenderer : public RendererComponent
	{
	public:
		std::string meshName;
	public:
		void Update(float dt);
		// Inherited via RendererComponent
		void Draw(Renderer& renderer);


	};
}
