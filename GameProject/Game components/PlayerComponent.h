#pragma once
#include "Components/Component.h"

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
private:
    int m_PlayerID{ -1 };
};






