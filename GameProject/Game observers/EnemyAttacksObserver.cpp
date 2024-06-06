#include "EnemyAttacksObserver.h"

#include "DataStructs.h"
#include "Initializers.h"
#include "Components/CollisionComponent.h"
#include "Components/SpriteComponent.h"
#include "Game components/Enemy components/BeamComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"
EnemyAttacksObserver::EnemyAttacksObserver(GameEngine::Scene* scene): m_Scene(scene) {}
void EnemyAttacksObserver::Notify(GameEngine::Subject* subject, int event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        int otherId = collisionData->pOtherCollider->GetID();
        if (otherId == static_cast<int>(GameId::player))
        {
            if (actor->GetID() == static_cast<int>(GameId::enemyBullet)) actor->SetDestroyedFlag();
            if (actor->GetID() == static_cast<int>(GameId::bossBeam))
            {
                BossGalagaComponent* bossComp = dynamic_cast<BossGalagaComponent*>(actor->GetComponent<BeamComponent>()->GetParentComp());
                if(!bossComp->HasCapturedFighter())
                {
                    bossComp->CapturedFighter();
                    auto capturedFighter = InitCapturedFighter(bossComp);
                    capturedFighter->AddObserver(static_cast<int>(ObserverIdentifier::enemyAttack), this);
                    m_Scene->AddObject(std::move(capturedFighter));
                }
            }
        }
    }
    break;
    case GameEvent::bulletShot:
    {
        const auto playerPos = actor->GetComponent<EnemyComponent>()->GetPlayerComponent()->GetGameObjParent()->GetPosition();
        auto enemyPos = actor->GetPosition();
        auto bullet = InitEnemyBullet(TrajectoryMath::CalculateDirection(enemyPos, playerPos));

        enemyPos.y += bullet->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h;
        bullet->SetPosition(enemyPos);
        bullet->AddObserver(static_cast<int>(ObserverIdentifier::enemyAttack), this);
        m_Scene->AddObject(std::move(bullet));

        //shoot a second bullet if the enemy is a boss that has a fighter captured
        auto bossComp = dynamic_cast<BossGalagaComponent*>(actor->GetComponent<EnemyComponent>());
        if (bossComp && bossComp->HasCapturedFighter())
        {
            bullet = InitEnemyBullet(TrajectoryMath::CalculateDirection(enemyPos, playerPos));
            bullet->SetPosition(enemyPos);
            bullet->AddObserver(static_cast<int>(ObserverIdentifier::enemyAttack), this);
            m_Scene->AddObject(std::move(bullet));
        }
    }
    break;
    case GameEvent::bulletOutOfBounds:
        actor->SetDestroyedFlag();
        break;
    case GameEvent::bossShotBeam:
    {
        auto enemyPos = actor->GetPosition();
        auto enemyComp = actor->GetComponent<EnemyComponent>();
        auto beam = InitBossBeam(enemyComp);

        enemyPos.y += actor->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.h;
        enemyPos.x += actor->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.w / 2.f;
        enemyPos.x -= beam->GetComponent<GameEngine::SpriteComponent>()->m_DestRect.w / 2.f;

        beam->SetPosition(enemyPos);
        beam->AddObserver(static_cast<int>(ObserverIdentifier::enemyAttack), this);
        m_Scene->AddObject(std::move(beam));
    }
    break;
    case GameEvent::beamRetracted:
    {
        actor->SetDestroyedFlag();
        auto parentComp = actor->GetComponent<BeamComponent>()->GetParentComp();
        parentComp->GetInIdleState();
    }
    break;
    default: break;
    }
}
