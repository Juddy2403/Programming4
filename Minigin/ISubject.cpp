#include "ISubject.h"

void GameEngine::ISubject::AddObserver(int message,IObserver* observer)
{
	auto it = m_Observers.find(message);
	if (it == m_Observers.end()) m_Observers[message] = ObserverList();
	m_Observers[message].push_front(observer);
}

void GameEngine::ISubject::RemoveObserver(int message, IObserver* observer)
{
	if(m_Observers.find(message) != m_Observers.end())
	m_Observers[message].remove(observer);
}

void GameEngine::ISubject::NotifyAll()
{
	for (auto it = m_Observers.begin(); it != m_Observers.end(); ++it)
	{
		for (auto& observer : m_Observers[it->first])
			observer->Update(this);
	}
}

void GameEngine::ISubject::Notify(int message)
{
	for (auto& observer : m_Observers[message])
		observer->Update(this);
}
