#pragma once
#include <unordered_map>
#include "IObserver.h"
#include "DataStructs.h"

class ScoreManager : public GameEngine::IObserver
{
public:
    void AddScore(int playerId, EnemyId enemyId);
    virtual void Notify(GameEngine::Subject* subject, GameEngine::GameEvent event
        , GameEngine::EventData* eventData) override;
    static int GetPlayerScore(int playerId);
private:
    static std::unordered_map<int, int> m_PlayerScores;
    const static std::unordered_map<EnemyId, int> m_EnemyScores;
};
