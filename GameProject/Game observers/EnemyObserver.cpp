#include "EnemyObserver.h"

#include "DataStructs.h"
#include "EventData.h"
#include "Game components/BulletComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Sound/ServiceLocator.h"
#include "Subjects/GameObject.h"

EnemyObserver::EnemyObserver() {}
void EnemyObserver::Notify(GameEngine::Subject* subject, int event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    //GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        if (collisionData->pOtherCollider->GetID() == static_cast<int>(GameId::bullet))
        {
            GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
            auto enemyComp = actor->GetComponent<EnemyComponent>();
            GameEngine::ServiceLocator::GetSoundSystem().PlaySound(static_cast<GameEngine::SoundId>(SoundId::enemyDeath), 100);
            if(bool hasDied = enemyComp->HasBeenHit())
            {
                int playerId = collisionData->pOtherCollider->GetComponent<BulletComponent>()->GetPlayerID();
                ScoreData scoreData;
                scoreData.enemyId = static_cast<int>(enemyComp->GetEnemyID());
                scoreData.playerId = playerId;
                subject->Notify(static_cast<int>(GameEvent::scoreIncrease),static_cast<int>(ObserverIdentifier::score),&scoreData);
                subject->NotifyAll(static_cast<int>(GameEvent::died));
            }
        }
        //std::cout<<"Enemy collided with: "<<collisionData->pOtherCollider->GetID()<< '\n';
    }
        break;
    default: break;
    }
}
