#include "EnemyObserver.h"

#include "DataStructs.h"
#include "EventData.h"
#include "Game components/BulletComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Sound/ServiceLocator.h"
#include "Subjects/GameObject.h"

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
