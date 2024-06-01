#include "FighterObserver.h"

#include "DataStructs.h"

void FighterObserver::Notify(GameEngine::Subject* subject, int event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    subject;
    switch(static_cast<GameEvent>(event)) {
    case GameEvent::hasBeenHit:
        break;
    case GameEvent::bulletShot:
        break;
    case GameEvent::bulletOutOfBounds:
        break;
    case GameEvent::collision:
        break;
    case GameEvent::event:
        break;
    }

}
