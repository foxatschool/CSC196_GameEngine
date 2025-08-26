#pragma once
#include "Core/Singleton.h"
#include "Event.h"
#include "Observer.h"
#include <map>
#include <list>

#define OBSERVER_ADD(event_id)				shovel::EventManager::Instance().AddObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				shovel::EventManager::Instance().RemoveObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	shovel::EventManager::Instance().Notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				shovel::EventManager::Instance().Notify({ #event_id, true })

namespace shovel
{
	class EventManager : public Singleton<EventManager>
	{
	public:
		void AddObserver(const Event::id_t id, IObserver& observer);
		void RemoveObserver(IObserver& observer);

		void Notify(const Event& event);

		void RemoveAll() { m_observers.clear(); }

	private:
		std::map<Event::id_t, std::list<IObserver*>> m_observers;

	};
}