#include "BossStage.h"

#include "Components/SpriteComponent.h"
#include "Subjects/GameObject.h"

BossStage* BossStageOne::HasBeenHit(GameEngine::GameObject& bossObj)
{
    GameEngine::SpriteComponent* spriteComponent = bossObj.GetComponent<GameEngine::SpriteComponent>();
    spriteComponent->m_SpriteInfo.m_StartPos.y += spriteComponent->m_SpriteInfo.m_Height*2 + spriteComponent->m_SpriteInfo.m_Spacing*2;
    spriteComponent->UpdateSrcRect();
    return new BossStageTwo();
}
BossStage* BossStageTwo::HasBeenHit(GameEngine::GameObject& bossObj)
{
    bossObj.SetDestroyedFlag();
    return nullptr;
}
