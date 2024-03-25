#include "SceneManager.h"
#include "GameActor.h"
#include "Component.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "IObserver.h"

void GameEngine::SceneManager::Update()
{
	m_Scene->Update();
}

//void GameEngine::SceneManager::FixedUpdate()
//{
//
//}

void GameEngine::SceneManager::Render()
{
	m_Scene->Render();
}

GameEngine::Scene& GameEngine::SceneManager::CreateScene(const std::string& name)
{
	//------BACKGROUND--------
	m_Scene.reset(new Scene(name));
	auto gameObject = std::make_unique<GameObject>("Background");
	gameObject->AddComponent<TextureComponent>("background.tga");
	m_Scene->AddObject(std::move(gameObject));

	//------LOGO--------
	gameObject = std::make_unique<GameObject>("Logo");
	gameObject->SetPosition(216.f, 180.f);
	gameObject->AddComponent<TextureComponent>("logo.tga");
	m_Scene->AddObject(std::move(gameObject));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);
	auto smallerFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);

	//------TITLE--------
	gameObject = std::make_unique<GameObject>("Title");
	gameObject->SetPosition(80.f, 20.f);
	gameObject->AddComponent<TextComponent>(font, "Programming 4 Assignment");
	gameObject->AddComponent<TextureComponent>();
	m_Scene->AddObject(std::move(gameObject));

	//------FPSCOUNTER--------
	gameObject = std::make_unique<GameObject>("FPSCounter");
	gameObject->SetPosition(20.f, 80.f);
	gameObject->AddComponent<FPSComponent>(gameObject->AddComponent<TextComponent>(font, "160 FPS"));
	gameObject->AddComponent<TextureComponent>();
	m_Scene->AddObject(std::move(gameObject));


	//-------EXTRATEXT---------
	gameObject = std::make_unique<GameObject>();
	gameObject->SetPosition(20.f, 120.f);
	gameObject->AddComponent<TextComponent>(smallerFont, "Use D-Pad to move Pacman, X to inflict damage, A and B to pick up pellets");
	gameObject->AddComponent<TextureComponent>();
	m_Scene->AddObject(std::move(gameObject));

	gameObject = std::make_unique<GameObject>();
	gameObject->SetPosition(20.f, 140.f);
	gameObject->AddComponent<TextComponent>(smallerFont, "Use WASD to move Ms Pacman, C to inflict damage, Z and X to pick up pellets");
	gameObject->AddComponent<TextureComponent>();
	m_Scene->AddObject(std::move(gameObject));

	//------PACMAN--------
	auto gameActor = std::make_unique<GameActor>("Pacman",3,200.f);
	gameActor->SetPosition(250.f, 250.f);
	gameActor->AddComponent<TextureComponent>("pacman.png");
	auto& input = InputManager::GetInstance();
	input.BindCommand<MoveUp>(GameEngine::InputManager::InputKey::DPAD_UP, gameActor.get(), 0);
	input.BindCommand<MoveDown>(GameEngine::InputManager::InputKey::DPAD_DOWN, gameActor.get(), 0);
	input.BindCommand<MoveLeft>(GameEngine::InputManager::InputKey::DPAD_LEFT, gameActor.get(), 0);
	input.BindCommand<MoveRight>(GameEngine::InputManager::InputKey::DPAD_RIGHT, gameActor.get(), 0);
	input.BindCommand<TakeDamage>(GameEngine::InputManager::InputKey::CONTROLLER_X, gameActor.get(),0);
	input.BindCommand<BigScoreIncrease>(GameEngine::InputManager::InputKey::CONTROLLER_A, gameActor.get(), 0);
	input.BindCommand<SmallScoreIncrease>(GameEngine::InputManager::InputKey::CONTROLLER_B, gameActor.get(), 0);


	std::unique_ptr<RenderableObserver> observer = std::make_unique<GameEngine::HealthObserver>("Pacman health observer");
	observer->AddComponent<TextComponent>(smallerFont, "");
	observer->AddComponent<TextureComponent>();
	observer->SetPosition(20.f, 160.f);
	m_Scene->AddObserver(static_cast<int>(Subject::ObserverIdentifier::health), std::move(observer), gameActor.get());

	observer = std::make_unique<GameEngine::ScoreObserver>("Pacman score observer");
	observer->AddComponent<TextComponent>(smallerFont, "");
	observer->AddComponent<TextureComponent>();
	observer->SetPosition(20.f, 180.f);
	m_Scene->AddObserver(static_cast<int>(Subject::ObserverIdentifier::score), std::move(observer), gameActor.get());

	m_Scene->AddObject(std::move(gameActor));

	//------MSPACMAN--------
	gameActor = std::make_unique<GameActor>("Ms Pacman",3,400.f);
	gameActor->SetPosition(200.f, 160.f);
	gameActor->AddComponent<TextureComponent>("PacmanFemale.png");
	input.BindCommand<MoveUp>(GameEngine::InputManager::InputKey::W, gameActor.get());
	input.BindCommand<MoveDown>(GameEngine::InputManager::InputKey::S, gameActor.get());
	input.BindCommand<MoveLeft>(GameEngine::InputManager::InputKey::A, gameActor.get());
	input.BindCommand<MoveRight>(GameEngine::InputManager::InputKey::D, gameActor.get());
	input.BindCommand<TakeDamage>(GameEngine::InputManager::InputKey::C, gameActor.get());
	input.BindCommand<BigScoreIncrease>(GameEngine::InputManager::InputKey::Z, gameActor.get());
	input.BindCommand<SmallScoreIncrease>(GameEngine::InputManager::InputKey::X, gameActor.get());

	observer = std::make_unique<GameEngine::HealthObserver>("Ms Pacman health observer");
	observer->AddComponent<TextComponent>(smallerFont, "");
	observer->AddComponent<TextureComponent>();
	observer->SetPosition(20.f, 200.f);
	m_Scene->AddObserver(static_cast<int>(Subject::ObserverIdentifier::health), std::move(observer), gameActor.get());

	observer = std::make_unique<GameEngine::ScoreObserver>("Ms Pacman score observer");
	observer->AddComponent<TextComponent>(smallerFont, "");
	observer->AddComponent<TextureComponent>();
	observer->SetPosition(20.f, 220.f);
	m_Scene->AddObserver(static_cast<int>(Subject::ObserverIdentifier::score), std::move(observer), gameActor.get());

	m_Scene->AddObject(std::move(gameActor));

	//scene.Add(std::move(gameObject2));

	//gameObject = std::make_unique<GameObject>("IMGUI");
	//gameObject->AddComponent<IMGUIComponent>();
	//scene.Add(std::move(gameObject));

	return *m_Scene;
}
