#include "Observer.h"

namespace shovel
{
	IObserver::~IObserver()
	{
		OBSERVER_REMOVE_SELF;
	}
}