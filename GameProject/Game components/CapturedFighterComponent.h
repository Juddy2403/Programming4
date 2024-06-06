#pragma once
#include "Components/Component.h"
#include "Enemy components/BossGalagaComponent.h"

class CapturedFighterComponent : public GameEngine::Component
{
public:
    explicit CapturedFighterComponent(GameEngine::GameObject* gameObj,BossGalagaComponent* parent,GameEngine::SpriteComponent* spriteComponent);
    void Update() override;
private:
    std::unique_ptr<RotatingSprite> m_RotatingSprite{};
    std::unique_ptr<Trajectory> m_GetBackTrajectory{nullptr};
    BossGalagaComponent* m_Parent{};
    const float m_Speed{200.f};
    
};
