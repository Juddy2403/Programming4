#pragma once
#include <queue>
#include "Trajectory Logic/Trajectory.h"
#include "DataStructs.h"
#include "Components/Component.h"
#include "Enemy States/EnemyState.h"
#include "Game components/PlayerComponent.h"

class RotatingSpriteComponent;
namespace GameEngine
{
    class SpriteComponent;
}

class EnemyComponent : public GameEngine::Component
{
public:
    explicit EnemyComponent(GameEngine::GameObject* gameObj, GameEngine::SpriteComponent* spriteComponent,
        RotatingSpriteComponent* rotatingComponent, PlayerComponent* playerComponent);

    EnemyComponent(const EnemyComponent& other) = delete;
    EnemyComponent(EnemyComponent&& other) noexcept = delete;
    EnemyComponent& operator=(const EnemyComponent& other) = delete;
    EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;
    ~EnemyComponent() override = default;

    virtual void GetInAttackState() = 0;
    virtual void GetInIdleState();
    void SetFormationPosition(const glm::ivec2& formationPos);
    void SetFormationTrajectory(const std::queue<PathData>& pathDataQueue);
    Trajectory& GetFormationTrajectory() { return m_FormationTrajectory; }
    
    [[nodiscard]] glm::ivec2 GetFormationPosition() const { return m_FormationPosition; }
    [[nodiscard]] int GetInitXPos() const { return m_InitXPos; }
    [[nodiscard]] float GetSpeed() const { return m_Speed; }
    virtual void Update() override;
    virtual bool HasBeenHit() {Died();return true;}
    virtual void Died();
    [[nodiscard]] virtual EnemyId GetEnemyID() const = 0;

    int GetRotationStage(const glm::vec2& direction) const;
    void UpdateSprite(int rotationStage) const;
    bool UpdateTrajectory(Trajectory& trajectory) const;
    PlayerComponent* GetPlayerComponent() const { return m_PlayerComponent; }
    
    int m_SetOutTurn{};
    int m_Stage{};
protected:
    PlayerComponent* m_PlayerComponent{};
    std::unique_ptr<EnemyState> m_CurrentState;
    float m_Speed{ 300.f };
    GameEngine::SpriteComponent* m_SpriteComponent{};
    RotatingSpriteComponent* m_RotatingComponent{};
    glm::ivec2 m_FormationPosition{};
    const int m_NrOfRotationStages{};
    int m_InitXPos{};
    float m_CurrentTime{};
    int m_CurrentRotationStage{};
private:
    //TODO: make trajectories unique ptrs 
    Trajectory m_FormationTrajectory{};
};


