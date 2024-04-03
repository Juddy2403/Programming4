#include "Galaga.h"

#include "ActorComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"
#include "ResourceManager.h"
#include "InputManager.h"

using namespace GameEngine;
void Galaga::LoadLevel() const
{
    //------BACKGROUND--------
    auto scene = std::make_unique<Scene>("First level");
    auto gameObject = std::make_unique<GameObject>("Background");
    gameObject->AddComponent<TextureComponent>("background.tga");
    scene->AddObject(std::move(gameObject));

    //------LOGO--------
    gameObject = std::make_unique<GameObject>("Logo");
    gameObject->SetPosition(216.f, 180.f);
    gameObject->AddComponent<TextureComponent>("logo.tga");
    scene->AddObject(std::move(gameObject));

    auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
    auto smallerFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

    //------TITLE--------
    gameObject = std::make_unique<GameObject>("Title");
    gameObject->SetPosition(80.f, 20.f);
    gameObject->AddComponent<TextComponent>(font, "Programming 4 Assignment");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //------FPSCOUNTER--------
    gameObject = std::make_unique<GameObject>("FPSCounter");
    gameObject->SetPosition(20.f, 80.f);
    gameObject->AddComponent<FPSComponent>(gameObject->AddComponent<TextComponent>(font, "160 FPS"));
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));


    //-------EXTRATEXT---------
    gameObject = std::make_unique<GameObject>();
    gameObject->SetPosition(20.f, 120.f);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    gameObject = std::make_unique<GameObject>();
    gameObject->SetPosition(20.f, 140.f);
    gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move Ms Pacman, C to inflict damage, Z and X to pick up pellets");
    gameObject->AddComponent<TextureComponent>();
    scene->AddObject(std::move(gameObject));

    //------PACMAN--------
    gameObject = std::make_unique<GameObject>("Pacman");
    gameObject->SetPosition(250.f, 250.f);
    gameObject->AddComponent<TextureComponent>("pacman.png");
    gameObject->AddComponent<ActorComponent>(3);
    auto& input = InputManager::GetInstance();
    input.BindCommand(ControllerInputKey::dpadUp,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ 0.f,-1.f },200.f), 0);
    input.BindCommand(ControllerInputKey::dpadDown,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ 0.f,1.f },200.f), 0);
    input.BindCommand(ControllerInputKey::dpadLeft,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ -1.f,0.f },200.f), 0);
    input.BindCommand(ControllerInputKey::dpadRight,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ 1.f,0.f },200.f), 0);
    input.BindCommand(ControllerInputKey::X,
        std::make_unique<TakeDamage>(gameObject.get()), 0);
    input.BindCommand(ControllerInputKey::A,
        std::make_unique<BigScoreIncrease>(gameObject.get()), 0);
    input.BindCommand(ControllerInputKey::B,
        std::make_unique<SmallScoreIncrease>(gameObject.get()), 0);

    //------HealthObserver--------
    auto healthObject = std::make_unique<GameObject>("Lives Text");
    healthObject->SetPosition(20.f, 160.f);
    healthObject->AddComponent<TextureComponent>();
    healthObject->AddComponent<TextComponent>(smallerFont, "");
    auto healthObserver = std::make_unique<GameEngine::HealthObserver>("Pacman health observer",healthObject.get());
    scene->AddObject(std::move(healthObject));
    scene->AddObserver(static_cast<int>(ObserverIdentifier::health), std::move(healthObserver), gameObject.get());
    
    //------ScoreObserver--------
    auto scoreObject = std::make_unique<GameObject>("Score Text");
    scoreObject->SetPosition(20.f, 180.f);
    scoreObject->AddComponent<TextureComponent>();
    scoreObject->AddComponent<TextComponent>(smallerFont, "");
    auto scoreObserver = std::make_unique<GameEngine::ScoreObserver>("Pacman score observer",scoreObject.get());
    scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserver), gameObject.get());
    scene->AddObject(std::move(scoreObject));

    scene->AddObject(std::move(gameObject));

    //------MSPACMAN--------
    gameObject = std::make_unique<GameObject>("Ms Pacman");
    gameObject->SetPosition(200.f, 160.f);
    gameObject->AddComponent<TextureComponent>("PacmanFemale.png");
    gameObject->AddComponent<ActorComponent>(3);
    input.BindCommand(KeyboardInputKey::W,
       std::make_unique<Move>(gameObject.get(), glm::vec2{ 0.f,-1.f }, 400.f));
    input.BindCommand(KeyboardInputKey::S,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ 0.f,1.f }, 400.f));
    input.BindCommand(KeyboardInputKey::A,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ -1.f,0.f }, 400.f));
    input.BindCommand(KeyboardInputKey::D,
        std::make_unique<Move>(gameObject.get(), glm::vec2{ 1.f,0.f }, 400.f));
    input.BindCommand(KeyboardInputKey::C,
        std::make_unique<TakeDamage>(gameObject.get()));
    input.BindCommand(KeyboardInputKey::Z,
      std::make_unique<BigScoreIncrease>(gameObject.get()));
    input.BindCommand(KeyboardInputKey::X,
      std::make_unique<SmallScoreIncrease>(gameObject.get()));

    //------HealthObserver--------
    healthObject = std::make_unique<GameObject>("Lives Text");
    healthObject->SetPosition(20.f, 200.f);
    healthObject->AddComponent<TextureComponent>();
    healthObject->AddComponent<TextComponent>(smallerFont, "");
    healthObserver = std::make_unique<GameEngine::HealthObserver>("Ms Pacman health observer",healthObject.get());
    scene->AddObject(std::move(healthObject));
    scene->AddObserver(static_cast<int>(ObserverIdentifier::health), std::move(healthObserver), gameObject.get());
    
    //------ScoreObserver--------
    scoreObject = std::make_unique<GameObject>("Score Text");
    scoreObject->SetPosition(20.f, 220.f);
    scoreObject->AddComponent<TextureComponent>();
    scoreObject->AddComponent<TextComponent>(smallerFont, "");
    scoreObserver = std::make_unique<GameEngine::ScoreObserver>("Ms Pacman score observer",scoreObject.get());
    scene->AddObserver(static_cast<int>(ObserverIdentifier::score), std::move(scoreObserver), gameObject.get());
    scene->AddObject(std::move(scoreObject));
    
    scene->AddObject(std::move(gameObject));

    SceneManager::GetInstance().SetScene(std::move(scene));

}
