#pragma once
#include <glm/vec3.hpp>

#include "RotatingSprite.h"
#include "Components/Component.h"
#include "Components/SpriteComponent.h"
#include "Subjects/GameObject.h"
#include "Trajectory Logic/Trajectory.h"

class PlayerComponent final : public GameEngine::Component
{
public:
    explicit PlayerComponent(GameEngine::GameObject* gameObject,GameEngine::SpriteComponent* spriteComponent, int playerID);
    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) noexcept = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;
    ~PlayerComponent() override = default;
    
    [[nodiscard]] int GetPlayerID() const { return m_PlayerID; }
    static constexpr glm::vec3 m_RespawnPos{330,520,0};
    static constexpr int m_PlayerSpeed{ 200 };
    void GetCaptured(const glm::vec2& enemyPos);
    [[nodiscard]] bool IsCaptured() const { return m_IsGettingCaptured; }
    void RebindCommands() const;
    void Update() override;
private:
    std::unique_ptr<Trajectory> m_CapturedTrajectory{nullptr};
    GameEngine::SpriteComponent* m_SpriteComponent;
    std::unique_ptr<RotatingSprite> m_RotatingSprite;
    int m_CurrentRotationStage{};
    const float m_TimeBetweenStages{0.03f};
    float m_AccumTime{};
    bool m_IsGettingCaptured{ false };
    const float m_Speed{ 100 };
    int m_PlayerID{ -1 };
};






