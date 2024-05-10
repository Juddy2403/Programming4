#pragma once
#include "BulletComponent.h"
#include "DataStructs.h"
#include "EnemyComponents.h"
#include "GameCommands.h"
#include "GameObject.h"
#include "InputManager.h"
#include "PlayerComponent.h"

inline std::unique_ptr<GameEngine::GameObject> InitFighter()
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::player));
    gameObject->SetPosition(150.f, 450.f);
    gameObject->AddComponent<PlayerComponent>(0);
    auto* spriteComponent = gameObject->AddComponent<RotatingSpriteComponent>("Galaga2.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 1;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.05f;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 7;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 1;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 6;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = false;

    gameObject->AddComponent<GameEngine::CollisionComponent>(&spriteComponent->m_DestRect);
    // auto fighterObserver = std::make_unique<FighterObserver>("Fighter observer");
    // scene->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), std::move(fighterObserver), gameObject.get());
    
    gameObject->AddComponent<HealthComponent>(3);
    auto& input = GameEngine::InputManager::GetInstance();
    input.BindCommand(GameEngine::KeyboardInputKey::W,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 0.f,-1.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::S,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 0.f,1.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::A,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ -1.f,0.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::D,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 1.f,0.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::SPACE,
        std::make_unique<ShootBulletCommand>(gameObject.get()));

    return gameObject;
}

inline std::unique_ptr<GameEngine::GameObject> InitBullet(int playerID)
{
    auto bullet = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::bullet));
    
    auto* bulletSpriteComp = bullet->AddComponent<GameEngine::SpriteComponent>("Galaga2.png");
    bulletSpriteComp->m_SpriteInfo.m_Height = 16;
    bulletSpriteComp->m_SpriteInfo.m_Width = 16;
    bulletSpriteComp->m_SpriteInfo.m_Spacing = 2;
    bulletSpriteComp->m_SpriteInfo.m_StartPos = glm::vec2{307,118};
    bulletSpriteComp->m_SpriteInfo.m_NrOfCols = 1;
    bulletSpriteComp->m_SpriteInfo.m_NrOfRows = 1;
    bulletSpriteComp->m_IsActive = false;
    bulletSpriteComp->m_Scale = 2;
    bulletSpriteComp->UpdateSrcRect();
    bullet->AddComponent<BulletComponent>(playerID,bulletSpriteComp);

    bullet->AddComponent<GameEngine::CollisionComponent>(&bulletSpriteComp->m_DestRect);
    return bullet;
}

inline std::unique_ptr<GameEngine::GameObject> InitBee()
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("Galaga2.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 19;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 16;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 8;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = false;
    
    gameObject->AddComponent<BeeComponent>(spriteComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(&spriteComponent->m_DestRect);
   
    return gameObject;
}

inline std::unique_ptr<GameEngine::GameObject> InitButterfly()
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("Galaga2.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 55;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 16;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 8;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = false;
    
    gameObject->AddComponent<ButterflyComponent>(spriteComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(&spriteComponent->m_DestRect);

    return gameObject;
}

inline std::unique_ptr<GameEngine::GameObject> InitBossGalaga()
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("Galaga2.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 91;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 16;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 8;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = false;
    
    gameObject->AddComponent<BossGalagaComponent>(spriteComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(&spriteComponent->m_DestRect);

    return gameObject;
}