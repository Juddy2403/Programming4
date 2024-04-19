﻿#include "BulletComponent.h"

#include "GameObject.h"
#include "Minigin.h"
#include "TimeManager.h"

BulletComponent::BulletComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent):
    Component(gameObj),
    m_SpriteComponent(spriteComponent)
{}

void BulletComponent::Update()
{
    int bulletYPos = m_SpriteComponent->m_DestRect.y + m_SpriteComponent->m_DestRect.h;
    
    if (bulletYPos < 0)
    {
        GetGameObjParent()->Notify( GameEngine::GameEvent::bulletOutOfBounds,static_cast<int>(GameEngine::ObserverIdentifier::bullet));
        return;
    }

    GetGameObjParent()->GetLocalTransform().Translate(GameEngine::TimeManager::GetElapsed() * m_Velocity);
}
