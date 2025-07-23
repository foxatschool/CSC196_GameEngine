#pragma once
#include <memory>

namespace shovel
{
	class Game
	{
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void ShutDown() = 0;

	protected:
		std::unique_ptr<class Scene> m_scene;
	};
}