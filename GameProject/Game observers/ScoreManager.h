#pragma once
#include <unordered_map>
#include "IObserver.h"

enum class EnemyId;
class ScoreManager : public GameEngine::IObserver
{
public:
    virtual void Notify(GameEngine::Subject* subject, int event
        , GameEngine::EventData* eventData) override;
    static int GetPlayerScore(int playerId);
private:
    static void AddScore(int playerId, EnemyId enemyId);
    static std::unordered_map<int, int> m_PlayerScores;
    const static std::unordered_map<EnemyId, int> m_EnemyScores;
};
