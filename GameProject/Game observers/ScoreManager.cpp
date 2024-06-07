#include "ScoreManager.h"
#include <iostream>
#include "DataStructs.h"

std::unordered_map<int, int> ScoreManager::m_PlayerScores{};
const std::unordered_map<EnemyId, int> ScoreManager::m_EnemyScores{
    { EnemyId::bee,50 },
    { EnemyId::beeDiving,100 },
    { EnemyId::butterfly,80 },
    { EnemyId::butterflyDiving,160 },
    { EnemyId::bossGalaga,150 },
    { EnemyId::bossGalagaDiving,400 }
};

void ScoreManager::AddScore(int playerId, EnemyId enemyId)
{
    m_PlayerScores[playerId] += m_EnemyScores.at(enemyId);
#ifndef NDEBUG
    std::cout << "Player " << playerId << " has score: " << m_PlayerScores[playerId] << '\n';
#endif
}

void ScoreManager::Notify([[maybe_unused]] GameEngine::Subject* subject, int event,[[maybe_unused]] GameEngine::EventData* eventData)
{
    if(static_cast<GameEvent>(event) != GameEvent::scoreIncrease) return;
    if(const auto scoreData = reinterpret_cast<ScoreData*>(eventData))
    {
        AddScore(scoreData->playerId, static_cast<EnemyId>(scoreData->enemyId));
    }
    else std::cerr << "ScoreManager::Notify: Invalid ScoreData\n";
}

int ScoreManager::GetPlayerScore(int playerId)
{
    return m_PlayerScores[playerId];
}
