#pragma once
#include <forward_list>
#include <map>

namespace GameEngine
{
    struct EventData;
    //TODO: replace these enums with an int id. Declare the enums in the game not the engine
    enum class ObserverIdentifier
    {
        health,
        score,
        bullet,
        collision,
    };
    enum class GameEvent
    {
        hasBeenHit,
        died,
        scoreIncreased,
        bulletShot,
        bulletOutOfBounds,
        collision,
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
        void NotifyAll(GameEvent event, EventData* eventData = nullptr);
        void Notify(GameEvent event, int message, EventData* eventData = nullptr);

        Subject() = default;
        virtual ~Subject() = default;
        Subject(const Subject& other) = delete;
        Subject(Subject&& other) = delete;
        Subject& operator=(const Subject& other) = delete;
        Subject& operator=(Subject&& other) = delete;
    };
}
