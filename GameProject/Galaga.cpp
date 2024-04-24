#include "Galaga.h"

#include "PlayerComponent.h"
#include "BackgroundComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Component.h"
#include "DataStructs.h"
#include "Initializers.h"
#include "GameObject.h"
#include "IObserver.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "PlayerComponent.h"

using namespace GameEngine;
void Galaga::LoadLevel() const
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
    destRect.w = destRect.h = 612;
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
    gameObject->SetPosition(20.f, 140.f);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move Ms Pacman, C to inflict damage, Z and X to pick up pellets");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //------FIGHTER--------
    gameObject = InitFighter();
    auto bulletObserver = std::make_unique<BulletObserver>("Fighter bullet observer", scene.get());
    scene->AddObserver(static_cast<int>(GameEngine::ObserverIdentifier::bullet), std::move(bulletObserver), gameObject.get());

    //------HealthObserver--------
    auto healthObject = std::make_unique<GameObject>(static_cast<int>(GameId::observer));
    healthObject->SetPosition(20.f, 160.f);
    healthObject->AddComponent<TextureComponent>();
    healthObject->AddComponent<TextComponent>(smallerFont, "");
    auto healthObserver = std::make_unique<GameEngine::HealthObserver>("Pacman health observer", healthObject.get());
    scene->AddObject(std::move(healthObject));
    scene->AddObserver(static_cast<int>(ObserverIdentifier::health), std::move(healthObserver), gameObject.get());

    //------ScoreObserver--------
    auto scoreObject = std::make_unique<GameObject>(static_cast<int>(GameId::observer));
    scoreObject->SetPosition(20.f, 180.f);
    scoreObject->AddComponent<TextureComponent>();
    scoreObject->AddComponent<TextComponent>(smallerFont, "");
    auto scoreObserver = std::make_unique<GameEngine::ScoreObserver>("Pacman score observer", scoreObject.get());
    scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserver), gameObject.get());
    scene->AddObject(std::move(scoreObject));

    scene->AddObject(std::move(gameObject));

    //------ENEMIES--------
    gameObject = InitBee();
    gameObject->SetPosition(298, 130);
    auto enemyObserver = std::make_unique<EnemyObserver>("Bee observer");
    scene->AddObserver(-1, std::move(enemyObserver), gameObject.get());

    scene->AddObject(std::move(gameObject));

    gameObject = InitButterfly();
    gameObject->SetPosition(298, 70);
    enemyObserver = std::make_unique<EnemyObserver>("Butterfly observer");
    scene->AddObserver(-1, std::move(enemyObserver), gameObject.get());
    scene->AddObject(std::move(gameObject));

    gameObject = InitBossGalaga();
    gameObject->SetPosition(298, 38);
    enemyObserver = std::make_unique<EnemyObserver>("Boss galaga observer");
    scene->AddObserver(-1, std::move(enemyObserver), gameObject.get());
    scene->AddObject(std::move(gameObject));

    SceneManager::GetInstance().SetScene(std::move(scene));
}
