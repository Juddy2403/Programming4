#include "Initializers.h"
#include "Game components/BulletComponent.h"
#include "DataStructs.h"
#include "GameCommands.h"
#include "Game components/PlayerHealthComponent.h"
#include "Game components/PlayerComponent.h"
#include "Game components/RotatingSpriteComponent.h"
#include "Components/CollisionComponent.h"
#include "Components/SpriteComponent.h"
#include "Game components/Enemy components/BeamComponent.h"
#include "Game components/Enemy components/BeeComponent.h"
#include "Game components/Enemy components/BossGalagaComponent.h"
#include "Game components/Enemy components/ButterflyComponent.h"
#include "Game components/Enemy components/EnemyBulletComponent.h"
#include "Managers/InputManager.h"

std::unique_ptr<GameEngine::GameObject> InitFighter()
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::player));
    gameObject->AddComponent<PlayerComponent>(0);
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 1;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.05f;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 7;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 1;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 0;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = false;

    gameObject->AddComponent<GameEngine::CollisionComponent>(spriteComponent->m_DestRect);
    gameObject->SetPosition(150, 450);

    gameObject->AddComponent<PlayerHealthComponent>(3, spriteComponent);
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

std::unique_ptr<GameEngine::GameObject> InitBullet(int playerID)
{
    auto bullet = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::bullet));

    auto* bulletSpriteComp = bullet->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    bulletSpriteComp->m_SpriteInfo.m_Height = 16;
    bulletSpriteComp->m_SpriteInfo.m_Width = 16;
    bulletSpriteComp->m_SpriteInfo.m_StartPos = glm::vec2{ 127,1 };
    bulletSpriteComp->m_SpriteInfo.m_NrOfCols = 1;
    bulletSpriteComp->m_SpriteInfo.m_NrOfRows = 1;
    bulletSpriteComp->m_IsActive = false;
    bulletSpriteComp->m_Scale = 2;
    bulletSpriteComp->UpdateSrcRect();
    bullet->AddComponent<BulletComponent>(playerID, bulletSpriteComp);

    SDL_Rect collisionRect = bulletSpriteComp->m_DestRect;
    collisionRect.w /= 3;
    collisionRect.x += collisionRect.w;
    bullet->AddComponent<GameEngine::CollisionComponent>(collisionRect);
    return bullet;
}
std::unique_ptr<GameEngine::GameObject> InitEnemyBullet(const glm::vec2& direction)
{
    auto bullet = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemyBullet));

    auto* bulletSpriteComp = bullet->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    bulletSpriteComp->m_SpriteInfo.m_Height = 16;
    bulletSpriteComp->m_SpriteInfo.m_Width = 16;
    bulletSpriteComp->m_SpriteInfo.m_StartPos = glm::vec2{ 145,1 };
    bulletSpriteComp->m_SpriteInfo.m_NrOfCols = 1;
    bulletSpriteComp->m_SpriteInfo.m_NrOfRows = 1;
    bulletSpriteComp->m_IsActive = false;
    bulletSpriteComp->m_Scale = 2;
    bulletSpriteComp->UpdateSrcRect();
    bullet->AddComponent<EnemyBulletComponent>(direction);

    SDL_Rect collisionRect = bulletSpriteComp->m_DestRect;
    collisionRect.w /= 3;
    collisionRect.x += collisionRect.w;
    bullet->AddComponent<GameEngine::CollisionComponent>(collisionRect);
    return bullet;
}

std::unique_ptr<GameEngine::GameObject> InitBee(PlayerComponent* playerComponent)
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 19;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 5;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 0;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.8f;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = true;

    gameObject->AddComponent<BeeComponent>(spriteComponent,
        gameObject->AddComponent<RotatingSpriteComponent>(spriteComponent->m_SpriteInfo.m_NrOfCols),
        playerComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(spriteComponent->m_DestRect);

    return gameObject;
}

std::unique_ptr<GameEngine::GameObject> InitButterfly(PlayerComponent* playerComponent)
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 55;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 5;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 0;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.8f;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = true;

    gameObject->AddComponent<ButterflyComponent>(spriteComponent,
        gameObject->AddComponent<RotatingSpriteComponent>(spriteComponent->m_SpriteInfo.m_NrOfCols),
        playerComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(spriteComponent->m_DestRect);

    return gameObject;
}

std::unique_ptr<GameEngine::GameObject> InitBossGalaga(PlayerComponent* playerComponent)
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("GalagaUpdated.png");
    spriteComponent->m_SpriteInfo.m_Height = 16;
    spriteComponent->m_SpriteInfo.m_Width = 16;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 91;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 5;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 2;
    spriteComponent->m_SpriteInfo.m_CurrentCol = 0;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.8f;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = true;

    gameObject->AddComponent<BossGalagaComponent>(spriteComponent,
        gameObject->AddComponent<RotatingSpriteComponent>(spriteComponent->m_SpriteInfo.m_NrOfCols),
        playerComponent);
    gameObject->AddComponent<GameEngine::CollisionComponent>(spriteComponent->m_DestRect);

    return gameObject;
}
std::unique_ptr<GameEngine::GameObject> InitBossBeam(EnemyComponent* parentComp)
{
    auto gameObject = std::make_unique<GameEngine::GameObject>(static_cast<int>(GameId::enemy));
    auto* spriteComponent = gameObject->AddComponent<GameEngine::SpriteComponent>("TractorBeam.png");
    spriteComponent->m_SpriteInfo.m_Height = 80;
    spriteComponent->m_SpriteInfo.m_Width = 48;
    spriteComponent->m_SpriteInfo.m_Spacing = 2;
    spriteComponent->m_SpriteInfo.m_StartPos.x = 1;
    spriteComponent->m_SpriteInfo.m_StartPos.y = 1;
    spriteComponent->m_SpriteInfo.m_NrOfCols = 3;
    spriteComponent->m_SpriteInfo.m_NrOfRows = 6;
    spriteComponent->m_SpriteInfo.m_TimeInterval = 0.15f;
    spriteComponent->m_Scale = 2;
    spriteComponent->UpdateSrcRect();
    spriteComponent->m_IsActive = true;
    gameObject->AddComponent<GameEngine::CollisionComponent>(spriteComponent->m_DestRect);
    gameObject->AddComponent<BeamComponent>(spriteComponent,parentComp);
    return gameObject;
}
