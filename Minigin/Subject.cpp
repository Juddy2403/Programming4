#include "Subject.h"
#include "IObserver.h"

void GameEngine::Subject::AddObserver(int message, IObserver* observer)
{
    const auto it = m_Observers.find(message);
    if (it == m_Observers.end()) m_Observers[message] = ObserverList();
    m_Observers[message].push_front(observer);
    m_Observers[message].front()->Notify(this, GameEvent::event);
}

void GameEngine::Subject::RemoveObserver(int message, IObserver* observer)
{
    if (m_Observers.find(message) != m_Observers.end())
        m_Observers[message].remove(observer);
}

void GameEngine::Subject::NotifyAll(GameEvent event, EventData* eventData)
{
    for (auto it = m_Observers.begin(); it != m_Observers.end(); ++it)
    {
        for (auto& observer : m_Observers[it->first])
            observer->Notify(this, event, eventData);
    }
}

void GameEngine::Subject::Notify(GameEvent event, int message, EventData* eventData)
{
    for (auto& observer : m_Observers[message])
        observer->Notify(this, event, eventData);
}
