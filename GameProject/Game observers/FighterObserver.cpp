#include "FighterObserver.h"

void FighterObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    subject;
    switch(event) {
    case GameEngine::GameEvent::hasBeenHit:
        break;
    case GameEngine::GameEvent::bulletShot:
        break;
    case GameEngine::GameEvent::bulletOutOfBounds:
        break;
    case GameEngine::GameEvent::collision:
        break;
    case GameEngine::GameEvent::event:
        break;
    }

}