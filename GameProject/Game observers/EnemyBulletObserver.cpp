﻿#include "EnemyBulletObserver.h"

#include "DataStructs.h"
#include "Initializers.h"
#include "Components/SpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
EnemyBulletObserver::EnemyBulletObserver(GameEngine::Scene* scene): m_Scene(scene) {}
void EnemyBulletObserver::Notify(GameEngine::Subject* subject, int event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        int otherId = collisionData->pOtherCollider->GetID();
        if (otherId == static_cast<int>(GameId::player) && actor->GetID() == static_cast<int>(GameId::enemyBullet))
        {
            actor->SetDestroyedFlag();
        }
    }
        break;
    case GameEvent::bulletShot:
    {
        const auto playerPos = actor->GetComponent<EnemyComponent>()->GetPlayerComponent()->GetGameObjParent()->GetPosition();
        const auto enemyPos = actor->GetPosition();
        auto bullet = InitEnemyBullet(TrajectoryMath::CalculateDirection(enemyPos,playerPos));

        glm::vec3 pos = actor->GetPosition();
        pos.y += bullet->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h;
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