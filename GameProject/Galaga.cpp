#include "Galaga.h"

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
#include "Trajectory Logic/Parsers.h"

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

    //------TITLE------
    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::text));
    gameObject->SetPosition(80, 20);
    gameObject->AddComponent<TextComponent>(font, "Galaga");
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
    
    auto enemyVec = Parser::ParseEnemyInfoByStage("../Data/Formations/EnemyInfoTest.json",
        "../Data/Formations/FormationTrajectories1.json");
    for (int i = 0; i < enemyVec.size(); ++i)
    {
        enemyVec[i]->AddObserver(-1, enemyObserver);
        enemyVec[i]->AddObserver(static_cast<int>(ObserverIdentifier::score), scoreObserver);
        scene->AddObject(std::move(enemyVec[i]));
    }

    //--------- Enemy formation component------------
    gameObject = std::make_unique<GameObject>(static_cast<int>(GameId::misc));
    gameObject->AddComponent<FormationComponent>();
    scene->AddObject(std::move(gameObject));
    
    SceneManager::GetInstance().SetScene(std::move(scene));
}
