#pragma once
#include "../Framework/Component.h"

namespace shovel
{
	class ColliderComponent : public Component
	{
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
}