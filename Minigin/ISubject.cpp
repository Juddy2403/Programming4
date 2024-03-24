#include "ISubject.h"
#include "IObserver.h"

void GameEngine::ISubject::AddObserver(int message,IObserver* observer)
{
	auto it = m_Observers.find(message);
	if (it == m_Observers.end()) m_Observers[message] = ObserverList();
	m_Observers[message].push_front(observer);
	m_Observers[message].front()->Notify(this);
}

void GameEngine::ISubject::RemoveObserver(int message, IObserver* observer)
{
	if(m_Observers.find(message) != m_Observers.end())
	m_Observers[message].remove(observer);
}

void GameEngine::ISubject::NotifyAll(GameEvent event)
{
	for (auto it = m_Observers.begin(); it != m_Observers.end(); ++it)
	{
		for (auto& observer : m_Observers[it->first])
			observer->Notify(event,this);
	}
}

void GameEngine::ISubject::Notify(GameEvent event,int message)
{
	for (auto& observer : m_Observers[message])
		observer->Notify(event,this);
}
