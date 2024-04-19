#include "Galaga.h"

#include "PlayerComponent.h"
#include "BackgroundComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Component.h"
#include "Fighter.h"
#include "GameObject.h"
#include "IObserver.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "PlayerComponent.h"

using namespace GameEngine;
void Galaga::LoadLevel() const
{
    //------BACKGROUND--------
    auto scene = std::make_unique<Scene>("First level");
    auto gameObject = std::make_unique<GameObject>("Background");
    SDL_Rect& destRect = gameObject->AddComponent<TextureComponent>("Background.png")->m_DestRect;
    destRect.w = destRect.h = 612;
    gameObject->AddComponent<BackgroundComponent>(gameObject->GetComponent<TextureComponent>(), 700);
    scene->AddObject(std::move(gameObject));

    auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    auto smallerFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

    //------TITLE--------
    gameObject = std::make_unique<GameObject>("Title");
    gameObject->SetPosition(80.f, 20.f);
    gameObject->AddComponent<TextComponent>(font, "Galaga");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //-------EXTRATEXT---------

    gameObject = std::make_unique<GameObject>();
    gameObject->SetPosition(20.f, 140.f);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move Ms Pacman, C to inflict damage, Z and X to pick up pellets");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //------FIGHTER--------
    gameObject = InitFighter(scene.get());

    //------HealthObserver--------
    auto healthObject = std::make_unique<GameObject>("Lives Text");
    healthObject->SetPosition(20.f, 160.f);
    healthObject->AddComponent<TextureComponent>();
    healthObject->AddComponent<TextComponent>(smallerFont, "");
    auto healthObserver = std::make_unique<GameEngine::HealthObserver>("Pacman health observer", healthObject.get());
    scene->AddObject(std::move(healthObject));
    scene->AddObserver(static_cast<int>(ObserverIdentifier::health), std::move(healthObserver), gameObject.get());

    //------ScoreObserver--------
    auto scoreObject = std::make_unique<GameObject>("Score Text");
    scoreObject->SetPosition(20.f, 180.f);
    scoreObject->AddComponent<TextureComponent>();
    scoreObject->AddComponent<TextComponent>(smallerFont, "");
    auto scoreObserver = std::make_unique<GameEngine::ScoreObserver>("Pacman score observer", scoreObject.get());
    scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserver), gameObject.get());
    scene->AddObject(std::move(scoreObject));
    
    scene->AddObject(std::move(gameObject));

    SceneManager::GetInstance().SetScene(std::move(scene));
}
