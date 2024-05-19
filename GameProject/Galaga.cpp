﻿#include "Galaga.h"

#include <fstream>
#include <SDL_rect.h>
#include <sstream>
#include "DataStructs.h"
#include "Initializers.h"
#include "Minigin.h"
#include "Scene.h"
#include "Components/TextComponent.h"
#include "Components/TextureComponent.h"
#include "Game components/BackgroundComponent.h"
#include "Game components/FormationComponent.h"
#include "Game components/Enemy components/EnemyComponent.h"
#include "Game observers/BulletObserver.h"
#include "Game observers/EnemyObserver.h"
#include "Game observers/ScoreManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/SceneManager.h"
#include "Sound/DerivedSoundSystems.h"
#include "Sound/ServiceLocator.h"
#include "Subjects/GameObject.h"

using namespace GameEngine;
void Galaga::LoadLevel()
{
    //----------SOUND----------------
#if NDEBUG
    ServiceLocator::RegisterSoundSystem(std::make_unique<SdlSoundSystem>());
#else
    ServiceLocator::RegisterSoundSystem(std::make_unique<LoggingSoundSystem>(std::make_unique<SdlSoundSystem>()));
#endif

    ServiceLocator::GetSoundSystem().FillSoundPaths("../Data/Audio/SoundPaths.txt");

    //------BACKGROUND--------
    auto scene = std::make_unique<Scene>("First level");
    auto gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::texture));
    SDL_Rect& destRect = gameObject->AddComponent<TextureComponent>("Background.png")->m_DestRect;
    destRect.w = GameEngine::g_WindowRect.w;
    destRect.h = GameEngine::g_WindowRect.h;
    gameObject->AddComponent<BackgroundComponent>(gameObject->GetComponent<TextureComponent>(), 700);
    scene->AddObject(std::move(gameObject));

    auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    auto smallerFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

    //------TITLE--------
    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::text));
    gameObject->SetPosition(80, 20);
    gameObject->AddComponent<TextComponent>(font, "Galaga");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //-------EXTRATEXT---------
    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::text));
    gameObject->SetPosition(20, 500);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move, press space to shoot a bullet and shoot the enemies for sound");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //--------FIGHTER--------
    gameObject = InitFighter();
    auto bulletObserver = std::make_unique<BulletObserver>(scene.get());
    scene->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), std::move(bulletObserver), gameObject.get());

    scene->AddObject(std::move(gameObject));

    //----------------ENEMIES--------------------
    auto enemyObserverUnique = std::make_unique<EnemyObserver>();
    auto enemyObserver = scene->AddObserver(-1, std::move(enemyObserverUnique), nullptr);
    auto scoreObserverUnique = std::make_unique<ScoreManager>();
    auto scoreObserver = scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserverUnique), nullptr);

    auto InitEnemyFromFile = [&](const std::string& filePath, std::function<std::unique_ptr<GameEngine::GameObject>()> initFunc) {
        std::ifstream file(filePath);
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty()) continue;
            line = line.substr(1, line.size() - 2);  // Remove the brackets
            std::stringstream ss(line);
            std::string xStr, yStr;

            std::getline(ss, xStr, ',');
            std::getline(ss, yStr);

            int x = std::stoi(xStr);
            int y = std::stoi(yStr);

            auto enemy = initFunc();
            enemy->SetPosition(x, y);
            enemy->GetComponent<EnemyComponent>()->SetFormationPosition({x,y});
            enemy->AddObserver(-1, enemyObserver);
            enemy->AddObserver(static_cast<int>(ObserverIdentifier::score), scoreObserver);
            scene->AddObject(std::move(enemy));
        }
    };

    // Use the lambda function to initialize enemies
    InitEnemyFromFile("../Data/Formations/Formation1Bees.txt", InitBee);
    InitEnemyFromFile("../Data/Formations/Formation1Butterflies.txt", InitButterfly);
    InitEnemyFromFile("../Data/Formations/Formation1Boss.txt", InitBossGalaga);

    //--------- Enemy formation component------------
    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::misc));
    gameObject->AddComponent<FormationComponent>();
    scene->AddObject(std::move(gameObject));
    
    SceneManager::GetInstance().SetScene(std::move(scene));
}
