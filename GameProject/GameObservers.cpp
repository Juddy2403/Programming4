#include "GameObservers.h"

#include <iostream>

#include "BulletComponent.h"
#include "Initializers.h"
#include "PlayerComponent.h"
#include "Sound/DerivedSoundSystems.h"
#include "EventData.h"
#include "ScoreManager.h"
#include "Sound/ServiceLocator.h"

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
BulletObserver::BulletObserver(GameEngine::Scene* scene):
    m_Scene(scene) {}
void BulletObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    // add the bullet game obj
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (event)
    {
    case GameEngine::GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        int otherId = collisionData->pOtherCollider->GetID();
        if (otherId == static_cast<int>(GameId::enemy) && actor->GetID() == static_cast<int>(GameId::bullet))
        {
            actor->SetDestroyedFlag();
        }
    }
        break;
    case GameEngine::GameEvent::bulletShot:
    {
        auto bullet = InitBullet(actor->GetComponent<PlayerComponent>()->GetPlayerID());

        glm::ivec3 pos = actor->GetPosition();
        pos.y -= bullet->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h;
        bullet->SetPosition(pos);

        bullet->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), this);

        m_Scene->AddObject(std::move(bullet));
    }
    break;
    case GameEngine::GameEvent::bulletOutOfBounds:
        actor->SetDestroyedFlag();
        break;
    default: break;
    }
}
EnemyObserver::EnemyObserver() {}
void EnemyObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    //GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (event)
    {
    case GameEngine::GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        //TODO: only broadcast event when necessary (use ids)
        if (collisionData->pOtherCollider->GetID() == static_cast<int>(GameId::bullet))
        {
            GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
            auto enemyComp = actor->GetComponent<EnemyComponent>();
            if(bool hasDied = enemyComp->HasBeenHit())
            {
                GameEngine::ServiceLocator::GetSoundSystem().PlaySound(static_cast<GameEngine::SoundId>(SoundId::enemyDeath), 100);
                int playerId = collisionData->pOtherCollider->GetComponent<BulletComponent>()->GetPlayerID();
                ScoreData scoreData;
                scoreData.enemyId = static_cast<int>(enemyComp->GetEnemyID());
                scoreData.playerId = playerId;
                subject->Notify(GameEngine::GameEvent::scoreIncrease,static_cast<int>(GameEngine::ObserverIdentifier::score),&scoreData);
            }
        }
        //std::cout<<"Enemy collided with: "<<collisionData->pOtherCollider->GetID()<< '\n';
    }
    break;
    default: break;
    }
}
