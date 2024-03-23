#pragma once
#include <forward_list>
#include <map>

namespace GameEngine {
	class IObserver;
	class ISubject
	{
	private:
		typedef std::forward_list<IObserver*> ObserverList;
		typedef std::map<int, ObserverList> ObserversMap;

		ObserversMap m_Observers;
	public:
		enum class ObserverMessages {
			health
		};

		virtual void AddObserver(int message, IObserver* observer);
		virtual void RemoveObserver(int message, IObserver* observer);
		virtual void NotifyAll();
		virtual void Notify(int message);

		ISubject() = default;
		virtual ~ISubject() = default;
		ISubject(const ISubject& other) = delete;
		ISubject(ISubject&& other) = delete;
		ISubject& operator=(const ISubject& other) = delete;
		ISubject& operator=(ISubject&& other) = delete;
	};
}

