#pragma once
#include <glm/vec2.hpp>

#include "DataStructs.h"
#include "EnemyState.h"
#include "Components/Component.h"

class RotatingSpriteComponent;
namespace GameEngine
{
    class SpriteComponent;
}

class EnemyComponent : public GameEngine::Component
{
public:
    explicit EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent);

    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) noexcept = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;
    ~EnemyComponent() override = default;

    void SetFormationPosition(const glm::ivec2& formationPos);
    void SetFormationTrajectory(const std::queue<PathData>& pathDataQueue);
    Trajectory& GetFormationTrajectory() { return m_FormationTrajectory; }
    
    [[nodiscard]] glm::ivec2 GetFormationPosition() const { return m_FormationPosition; }
    [[nodiscard]] int GetInitXPos() const { return m_InitXPos; }
    [[nodiscard]] float GetSpeed() const { return m_Speed; }
    virtual void Update() override;
    virtual bool HasBeenHit() = 0;
    [[nodiscard]] bool IsDiving() const { return m_IsDiving; }
    [[nodiscard]] virtual EnemyId GetEnemyID() const = 0;

    int GetRotationStage() const;
    void UpdateSprite(int rotationStage) const;
    
    int m_SetOutTurn{};
    int m_Stage{};
protected:
    std::unique_ptr<EnemyState> m_CurrentState;
    bool m_IsDiving{ false };
    float m_Speed{ 200.f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
    RotatingSpriteComponent* m_RotatingComponent{};
    glm::ivec2 m_FormationPosition{};
    const int m_NrOfRotationStages{};
    int m_InitXPos{};
    float m_CurrentTime{};
    int m_CurrentRotationStage{};
private:
    Trajectory m_FormationTrajectory{};
};


