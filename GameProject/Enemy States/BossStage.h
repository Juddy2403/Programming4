#pragma once

class EnemyComponent;
namespace GameEngine
{
    class GameObject;
}
// ┌────────────────────────┐                 ┌────────────────────────┐  
// │                        │ has been hit    │                        │  
// │        Stage 1         ├───────────────► │        Stage 2         ├─┐
// │                        │                 │                        │ │
// └────────────────────────┘                 ├────────────────────────┤ │
//                                            │change sprites          │ │
//                                            └────────────────────────┘ │
//                                                                       │
//                                                                       │
//                         ┌────────────────┐   has been hit             │
//                         │      Dies      │ ◄──────────────────────────┘
//                         ├────────────────┤                             
//                         │ score increases│                             
//                         └────────────────┘                             
class BossStage
{
public:
    virtual BossStage* HasBeenHit(EnemyComponent* bossObj) = 0;
    virtual ~BossStage() = default;
};

class BossStageOne final : public BossStage
{
public:
    virtual BossStage* HasBeenHit(EnemyComponent* bossObj) override;
    virtual ~BossStageOne() = default;
};

class BossStageTwo final : public BossStage
{
public:
    virtual BossStage* HasBeenHit(EnemyComponent* bossObj) override;
    virtual ~BossStageTwo() = default;
};
