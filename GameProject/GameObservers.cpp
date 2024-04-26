#include "GameObservers.h"

#include <iostream>

#include "BulletComponent.h"
#include "Initializers.h"
#include "PlayerComponent.h"
#include "DerivedSoundSystems.h"
#include "ServiceLocator.h"

BulletObserver::BulletObserver(std::string&& name, GameEngine::Scene* scene):
    IObserver(std::move(name)), m_Scene(scene) {}
void BulletObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    // add the bullet game obj
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (event)
    {
    case GameEngine::GameEvent::collision:
    {
        const auto collisionData = static_cast<GameEngine::CollisionData*>(eventData);
        if (collisionData->pOtherCollider->GetGameObjParent()->GetID() == static_cast<int>(GameId::enemy)&&
            actor->GetID() == static_cast<int>(GameId::bullet))
        {
            actor->SetDestroyedFlag();
        }
        std::cout<<"Bullet collided with: "<<collisionData->pOtherCollider->GetGameObjParent()->GetID()<<std::endl;
    }
        break;
    case GameEngine::GameEvent::bulletShot:
    {
        auto bullet = InitBullet();

        glm::vec3 pos = actor->GetPosition();
        pos.y -= static_cast<float>(bullet->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h);
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
EnemyObserver::EnemyObserver(std::string&& name): IObserver(std::move(name)) {}
void EnemyObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
    , [[maybe_unused]] GameEngine::EventData* eventData)
{
    //GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (event)
    {
    case GameEngine::GameEvent::collision:
    {
        const auto collisionData = static_cast<GameEngine::CollisionData*>(eventData);
        if (collisionData->pOtherCollider->GetGameObjParent()->GetID() == static_cast<int>(GameId::bullet))
        {
            GameEngine::ServiceLocator::GetSoundSystem().AddSoundToQueue(static_cast<GameEngine::SoundId>(SoundId::enemyDeath), 100);
            subject->NotifyAll(GameEngine::GameEvent::hasBeenHit);
        }
        std::cout<<"Enemy collided with: "<<collisionData->pOtherCollider->GetGameObjParent()->GetID()<< '\n';
    }
    break;
    case GameEngine::GameEvent::hasBeenHit:
        break;
    case GameEngine::GameEvent::died:
        break;
    default: break;
    }
}
