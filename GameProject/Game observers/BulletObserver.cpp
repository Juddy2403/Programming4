﻿#include "BulletObserver.h"

#include "DataStructs.h"
#include "Initializers.h"
#include "Components/SpriteComponent.h"
#include "Game components/PlayerComponent.h"

BulletObserver::BulletObserver(GameEngine::Scene* scene):
    m_Scene(scene) {}
void BulletObserver::Notify(GameEngine::Subject* subject, int event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    // add the bullet game obj
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        int otherId = collisionData->pOtherCollider->GetID();
        if (otherId == static_cast<int>(GameId::enemy) && actor->GetID() == static_cast<int>(GameId::bullet))
        {
            actor->SetDestroyedFlag();
        }
    }
        break;
    case GameEvent::bulletShot:
    {
        auto bullet = InitBullet(actor->GetComponent<PlayerComponent>()->GetPlayerID());

        glm::vec3 pos = actor->GetPosition();
        pos.y -= bullet->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h;
        bullet->SetPosition(pos);

        bullet->AddObserver(static_cast<int>(ObserverIdentifier::bullet), this);

        m_Scene->AddObject(std::move(bullet));
    }
        break;
    case GameEvent::bulletOutOfBounds:
        actor->SetDestroyedFlag();
        break;
    default: break;
    }
}