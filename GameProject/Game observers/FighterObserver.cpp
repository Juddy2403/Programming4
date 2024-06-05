#include "FighterObserver.h"

#include "DataStructs.h"
#include "Galaga.h"
#include "Game components/PlayerComponent.h"
#include "Game components/PlayerHealthComponent.h"
#include "Input/KeyboardInput.h"
#include "Managers/InputManager.h"
#include "Subjects/GameObject.h"

void FighterObserver::Notify(GameEngine::Subject* subject, int event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::hasBeenHit:
        break;
    case GameEvent::died:
        break;
    case GameEvent::collision:
    {
        const auto collisionData = reinterpret_cast<GameEngine::CollisionData*>(eventData);
        if (collisionData->pOtherCollider->GetID() == static_cast<int>(GameId::enemy) ||
            collisionData->pOtherCollider->GetID() == static_cast<int>(GameId::enemyBullet))
        {
            GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
            auto healthComp = actor->GetComponent<PlayerHealthComponent>();
            actor->SetPosition(PlayerComponent::m_RespawnPos);
            healthComp->Hit();
        }
        else if (collisionData->pOtherCollider->GetID() == static_cast<int>(GameId::bossBeam))
        {
            auto actor = dynamic_cast<GameEngine::GameObject*>(subject);
            if(actor->GetComponent<PlayerComponent>()->IsCaptured()) return;
            auto& input = GameEngine::InputManager::GetInstance();
            input.UnbindCommand(GameEngine::KeyboardInputKey::A);
            input.UnbindCommand(GameEngine::KeyboardInputKey::D);
            input.UnbindCommand(GameEngine::KeyboardInputKey::SPACE);
            actor->GetComponent<PlayerComponent>()->GetCaptured(collisionData->pOtherCollider->GetPosition());
        }
    }
    break;
    default: break;
    }
}
