#pragma once

namespace shovel
{
	class IObserver
	{
	public:
		virtual ~IObserver();
		
		virtual void OnNotify(const Event& event) = 0;
	};
}