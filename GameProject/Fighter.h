#pragma once
#include "GameCommands.h"
#include "GameObject.h"
#include "GameObservers.h"
#include "InputManager.h"
#include "PlayerComponent.h"

inline std::unique_ptr<GameEngine::GameObject> InitFighter(GameEngine::Scene* scene)
{
    auto gameObject = std::make_unique<GameEngine::GameObject>("Fighter");
    gameObject->SetPosition(150.f, 450.f);
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

    auto bulletObserver = std::make_unique<BulletObserver>("Fighter bullet observer", scene);
    scene->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), std::move(bulletObserver), gameObject.get());
    
    gameObject->AddComponent<ActorDataComponent>(3);
    auto& input = GameEngine::InputManager::GetInstance();
    input.BindCommand(GameEngine::KeyboardInputKey::W,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 0.f,-1.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::S,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 0.f,1.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::A,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ -1.f,0.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::D,
        std::make_unique<GameEngine::Move>(gameObject.get(), glm::vec2{ 1.f,0.f }, 200));
    input.BindCommand(GameEngine::KeyboardInputKey::C,
        std::make_unique<GameEngine::TakeDamage>(gameObject.get()));
    input.BindCommand(GameEngine::KeyboardInputKey::Z,
        std::make_unique<GameEngine::BigScoreIncrease>(gameObject.get()));
    input.BindCommand(GameEngine::KeyboardInputKey::X,
        std::make_unique<GameEngine::SmallScoreIncrease>(gameObject.get()));
    input.BindCommand(GameEngine::KeyboardInputKey::SPACE,
        std::make_unique<ShootBulletCommand>(gameObject.get()));

    return gameObject;
}
