#pragma once
#include <fstream>
#include <queue>
#include <json.hpp>

#include "Initializers.h"
#include "PathDataStruct.h"

namespace Parser
{
    inline std::queue<PathData> ParseTrajectory(const std::string& filePath)
    {
        std::queue<PathData> pathDataQueue;
        std::ifstream fileStream(filePath);
        nlohmann::json jsonData;
        fileStream >> jsonData;

        for (const auto& element : jsonData)
        {
            PathData pathData{};
            pathData.isRotating = element["isRotating"].get<bool>();
            if (pathData.isRotating)
            {
                pathData.isRotatingClockwise = element["isRotatingClockwise"].get<bool>();
                pathData.totalRotationAngle = element["totalRotationAngle"].get<float>();
                pathData.centerOfRotation.x = element["centerOfRotation"][0].get<float>();
                pathData.centerOfRotation.y = element["centerOfRotation"][1].get<float>();
            }
            else
            {
                pathData.destination.x = element["destination"][0].get<float>();
                pathData.destination.y = element["destination"][1].get<float>();
            }
            pathDataQueue.push(pathData);
        }

        return pathDataQueue;
    }
    inline std::vector<std::unique_ptr<GameEngine::GameObject>> ParseEnemyInfo(const std::string& filePath)
    {
        std::unique_ptr<GameEngine::GameObject> enemy;
        std::vector<std::unique_ptr<GameEngine::GameObject>> enemyVec;
        std::ifstream fileStream(filePath);
        nlohmann::json jsonData;
        fileStream >> jsonData;

        for (const auto& element : jsonData)
        {
            std::string enemyType = element["enemyType"];
            if(enemyType == "Bee") enemy = InitBee();
            else if(enemyType == "Butterfly") enemy = InitButterfly();
            else if(enemyType == "BossGalaga") enemy = InitBossGalaga();
            
            glm::vec2 pos = { element["formationPosition"][0].get<int>(),element["formationPosition"][1].get<int>() };
            enemy->SetPosition(0, 0);
            enemy->GetComponent<EnemyComponent>()->SetFormationPosition({ pos.x,pos.y });
            enemyVec.emplace_back(std::move(enemy));
        }
        return enemyVec;
    }
}
