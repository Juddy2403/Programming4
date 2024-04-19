#include "GameObservers.h"

#include "BulletComponent.h"
#include "PlayerComponent.h"

BulletObserver::BulletObserver(std::string&& name, GameEngine::Scene* scene):
IObserver(std::move(name)), m_Scene(scene){}
void BulletObserver::Notify(GameEngine::Subject* subject, GameEngine::GameEvent event)
{
    // add the bullet game obj
    GameEngine::GameObject* actor = dynamic_cast<GameEngine::GameObject*>(subject);
    switch (event)
    {
    case GameEngine::GameEvent::bulletShot:
    {
        auto bullet = std::make_unique<GameEngine::GameObject>();
        glm::vec3 pos = actor->GetPosition();
        auto* spriteComp = actor->GetComponent<RotatingSpriteComponent>();
        pos.y -= static_cast<float>(spriteComp->m_DestRect.h);
        bullet->SetPosition(pos);
        auto* bulletSpriteComp = bullet->AddComponent<GameEngine::SpriteComponent>("Galaga2.png");
        bulletSpriteComp->m_SpriteInfo = spriteComp->m_SpriteInfo;
        bulletSpriteComp->m_SpriteInfo.m_StartPos = glm::vec2{307,118};
        bulletSpriteComp->m_SpriteInfo.m_CurrentCol = bulletSpriteComp->m_SpriteInfo.m_CurrentRow = 0;
        bulletSpriteComp->m_SpriteInfo.m_NrOfCols = 1;
        bulletSpriteComp->m_SpriteInfo.m_NrOfRows = 1;
        bulletSpriteComp->m_IsActive = false;
        bulletSpriteComp->m_Scale = spriteComp->m_Scale;
        bulletSpriteComp->UpdateSrcRect();
        bullet->AddComponent<BulletComponent>(bulletSpriteComp);
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