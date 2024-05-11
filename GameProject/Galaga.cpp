#include "Galaga.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "BackgroundComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Component.h"
#include "DataStructs.h"
#include "Initializers.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "DerivedSoundSystems.h"
#include "GameObservers.h"
#include "Minigin.h"

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
    gameObject->SetPosition(80.f, 20.f);
    gameObject->AddComponent<TextComponent>(font, "Galaga");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //-------EXTRATEXT---------

    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::text));
    gameObject->SetPosition(20.f, 500.f);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move, press space to shoot a bullet and shoot the enemies for sound");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //------FIGHTER--------
    gameObject = InitFighter();
    auto bulletObserver = std::make_unique<BulletObserver>(scene.get());
    scene->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), std::move(bulletObserver), gameObject.get());

    // //------HealthObserver--------
    // auto healthObject = std::make_unique<GameObject>(static_cast<int>(GameId::observer));
    // healthObject->SetPosition(20.f, 160.f);
    // healthObject->AddComponent<TextureComponent>();
    // healthObject->AddComponent<TextComponent>(smallerFont, "");
    // auto healthObserver = std::make_unique<GameEngine::HealthObserver>("Pacman health observer", healthObject.get());
    // scene->AddObject(std::move(healthObject));
    // scene->AddObserver(static_cast<int>(ObserverIdentifier::health), std::move(healthObserver), gameObject.get());
    //
    // //------ScoreObserver--------
    // auto scoreObject = std::make_unique<GameObject>(static_cast<int>(GameId::observer));
    // scoreObject->SetPosition(20.f, 180.f);
    // scoreObject->AddComponent<TextureComponent>();
    // scoreObject->AddComponent<TextComponent>(smallerFont, "");
    // auto scoreObserver = std::make_unique<GameEngine::ScoreObserver>("Score observer", scoreObject.get());
    // scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserver), gameObject.get());
    // scene->AddObject(std::move(scoreObject));

    scene->AddObject(std::move(gameObject));

    //----------------ENEMIES--------------------
    auto enemyObserverUnique = std::make_unique<EnemyObserver>();
    auto enemyObserver = scene->AddObserver(-1, std::move(enemyObserverUnique), nullptr);

    //------BEE--------
    std::ifstream fileBee("../Data/Formations/Formation1Bees.txt");
    std::string line;
    while (std::getline(fileBee, line))
    {
        if(line.empty()) continue;
        line = line.substr(1, line.size() - 2);  // Remove the brackets
        std::stringstream ss(line);
        std::string xStr, yStr;

        std::getline(ss, xStr, ',');
        std::getline(ss, yStr);

        float x = std::stof(xStr);
        float y = std::stof(yStr);

        gameObject = InitBee();
        gameObject->SetPosition(x, y);
        gameObject->AddObserver(-1,enemyObserver);
        scene->AddObject(std::move(gameObject));
    }

    //------BUTTERFLY--------
    std::ifstream fileButterfly("../Data/Formations/Formation1Butterflies.txt");
    while (std::getline(fileButterfly, line))
    {
        if(line.empty()) continue;
        line = line.substr(1, line.size() - 2);  // Remove the brackets
        std::stringstream ss(line);
        std::string xStr, yStr;

        std::getline(ss, xStr, ',');
        std::getline(ss, yStr);

        float x = std::stof(xStr);
        float y = std::stof(yStr);

        gameObject = InitButterfly();
        gameObject->SetPosition(x, y);
        gameObject->AddObserver(-1,enemyObserver);
        scene->AddObject(std::move(gameObject));
    }

    //------BOSS GALAGA--------
    std::ifstream fileBoss("../Data/Formations/Formation1Boss.txt");
    while (std::getline(fileBoss, line))
    {
        if(line.empty()) continue;
        line = line.substr(1, line.size() - 2);  // Remove the brackets
        std::stringstream ss(line);
        std::string xStr, yStr;

        std::getline(ss, xStr, ',');
        std::getline(ss, yStr);

        float x = std::stof(xStr);
        float y = std::stof(yStr);

        gameObject = InitBossGalaga();
        gameObject->SetPosition(x, y);
        gameObject->AddObserver(-1,enemyObserver);
        scene->AddObject(std::move(gameObject));
    }
    SceneManager::GetInstance().SetScene(std::move(scene));
}

