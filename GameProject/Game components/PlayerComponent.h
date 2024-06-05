#pragma once
#include <glm/vec3.hpp>

#include "Components/Component.h"
#include "Subjects/GameObject.h"
#include "Trajectory Logic/Trajectory.h"

class PlayerComponent final : public GameEngine::Component
{
public:
    explicit PlayerComponent(GameEngine::GameObject* gameObject, int playerID);
    PlayerComponent(const PlayerComponent& other) = delete;
    PlayerComponent(PlayerComponent&& other) noexcept = delete;
    PlayerComponent& operator=(const PlayerComponent& other) = delete;
    PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;
    ~PlayerComponent() override = default;
    
    [[nodiscard]] int GetPlayerID() const { return m_PlayerID; }
    static constexpr glm::vec3 m_RespawnPos{330,520,0};
    void GetCaptured(const glm::vec2& enemyPos);
    [[nodiscard]] bool IsCaptured() const { return m_IsGettingCaptured; }
    void Update() override;
private:
    std::unique_ptr<Trajectory> m_CapturedTrajectory{nullptr};
    bool m_IsGettingCaptured{ false };
    const float m_Speed{ 200 };
    int m_PlayerID{ -1 };
};






