#include "CircleCollider2D.h"

namespace shovel
{
	bool CircleCollider2D::CheckCollision(ColliderComponent& other)
	{
		float distance = (owner->transform.position - other.owner->transform.position).Length();
		//
		auto circleCollider = dynamic_cast<CircleCollider2D*>(&other);
		if (circleCollider)
		{
			float radii = radius + circleCollider->radius;
			if (distance <= radii)
			{
				return true;
			}
		}
		return false;
	}
	void CircleCollider2D::Read(const json::value_t& value)
	{

	}
}