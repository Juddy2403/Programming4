#pragma once
#include "Components/Component.h"

class FormationComponent final : public GameEngine::Component
{
public:
    explicit FormationComponent(GameEngine::GameObject* gameObj);
    void Update() override;
    ~FormationComponent() override = default;
    static float GetOffset();
    static void ToggleUpdate() { m_IsUpdating = !m_IsUpdating; }
private:
    static bool m_IsUpdating;
    static bool m_DoesExist;
    static float m_Offset;
    static int m_Direction;
    static constexpr int m_OffsetLimit{150};
    static constexpr float m_Speed{100.f};
};
