﻿#pragma once
#include <unordered_map>
#include "DataStructs.h"

class ScoreManager
{
public:
    static void AddScore(int playerId, EnemyId enemyId);
    static int GetPlayerScore(int playerId);
private:
    static std::unordered_map<int,int> m_PlayerScores;
    const static std::unordered_map<EnemyId,int> m_EnemyScores;
};