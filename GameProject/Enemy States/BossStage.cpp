﻿#include "BossStage.h"

#include "Components/SpriteComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Subjects/GameObject.h"

BossStage* BossStageOne::HasBeenHit(EnemyComponent* bossObj)
{
    GameEngine::SpriteComponent* spriteComponent = bossObj->GetGameObjParent()->GetComponent<GameEngine::SpriteComponent>();
    spriteComponent->m_SpriteInfo.m_StartPos.y += spriteComponent->m_SpriteInfo.m_Height*2 + spriteComponent->m_SpriteInfo.m_Spacing*2;
    spriteComponent->UpdateSrcRect();
    return new BossStageTwo();
}
BossStage* BossStageTwo::HasBeenHit(EnemyComponent* bossObj)
{
    bossObj->Died();
    return nullptr;
}
