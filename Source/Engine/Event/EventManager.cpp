#include "EnginePCH.h"
#include "Core/StringHelper.h"

namespace shovel
{
	void EventManager::AddObserver(const Event::id_t id, IObserver& observer)
	{
		m_observers[id].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer)
	{
		IObserver* observerPtr = &observer;

		// Iterate through all event types
		for (auto& eventType : m_observers)
		{
			// Get the list of observers for this event type
			auto observers = eventType.second;

			// Remove the observer from the maching event type
			std::erase_if(observers, [observerPtr](auto observer)
			{
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event)
	{
		//Find observers of event
		auto it = m_observers.find(toLower(event.id));
		if (it != m_observers.end())
		{
			//get observers of event
			auto& observers = it->second;

			for (auto observer : observers)
			{
				observer->OnNotify(event);
			}
		}
		else
		{
			Logger::Warning("Could not find event {}", event.id);
		}
	}
}

