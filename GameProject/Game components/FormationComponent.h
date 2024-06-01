#pragma once
#include "Scene.h"
#include "Components/Component.h"

class FormationComponent final : public GameEngine::Component
{
public:
    explicit FormationComponent(GameEngine::GameObject* gameObj);
    void Update() override;
    void LoadFormation(GameEngine::Scene* scene,std::vector<std::vector<std::unique_ptr<GameEngine::GameObject>>>&& formation,
        const std::vector<GameEngine::IObserver*>& observers);
    ~FormationComponent() override = default;
    static float GetOffset();
    static void ToggleUpdate() { m_IsUpdating = !m_IsUpdating; }
private:
    std::vector<std::vector<std::unique_ptr<GameEngine::GameObject>>> m_Formation;
    std::vector<GameEngine::GameObject*> m_CurrentlyLoadedEnemies;
    std::vector<GameEngine::IObserver*> m_Observers;
    GameEngine::Scene* m_Scene;
    int m_CurrentStage;
    int m_Stages;
    bool m_LoadedStage{false};
    static bool m_IsUpdating;
    static bool m_DoesExist;
    static float m_Offset;
    static int m_Direction;
    static constexpr int m_OffsetLimit{150};
    static constexpr float m_Speed{100.f};
};
