#pragma once
#include <forward_list>
#include <map>

namespace GameEngine {
	enum class ObserverIdentifier {
		health,
		score
	};
	enum class GameEvent {
		playerDied,
		scoreIncreased,
		event //for when smth generic happens
	};
	class IObserver;
	class Subject
	{
	private:
		typedef std::forward_list<IObserver*> ObserverList;
		typedef std::map<int, ObserverList> ObserversMap;

		ObserversMap m_Observers;
	public:
		void AddObserver(int message, IObserver* observer);
		void RemoveObserver(int message, IObserver* observer);
		void NotifyAll(GameEvent event);
		void Notify(GameEvent event,int message);

		Subject() = default;
		virtual ~Subject() = default;
		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;
	};
}

