#include "SceneManager.h"
#include "GameActor.h"
#include "Component.h"
#include "InputManager.h"
#include "ResourceManager.h"

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
	//const auto& scene = std::make_unique<Scene>(name);
	m_Scene.reset(new Scene(name));
	auto gameObject = std::make_unique<GameObject>("Background");
	gameObject->AddComponent<TextureComponent>("background.tga");
	m_Scene->Add(std::move(gameObject));

	gameObject = std::make_unique<GameObject>("Logo");
	gameObject->SetPosition(216.f, 180.f);
	gameObject->AddComponent<TextureComponent>("logo.tga");
	m_Scene->Add(std::move(gameObject));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	gameObject = std::make_unique<GameObject>("Title");
	gameObject->SetPosition(80.f, 20.f);
	gameObject->AddComponent<TextComponent>(font, "Programming 4 Assignment");
	gameObject->AddComponent<TextureComponent>();
	m_Scene->Add(std::move(gameObject));

	gameObject = std::make_unique<GameObject>("FPSCounter");
	gameObject->SetPosition(20.f, 80.f);
	gameObject->AddComponent<FPSComponent>(gameObject->AddComponent<TextComponent>(font, "160 FPS"));
	gameObject->AddComponent<TextureComponent>();
	m_Scene->Add(std::move(gameObject));

	//auto gameObject2 = std::make_unique<GameObject>("CenterPoint");
	//gameObject2->SetPosition(300.f, 300.f);

	auto gameActor = std::make_unique<GameActor>("Pacman",3,200.f);
	gameActor->SetPosition(250.f, 250.f);
	//gameObject->SetParent(gameObject2.get());
	gameActor->AddComponent<TextureComponent>("pacman.png");
	//gameObject->AddComponent<RotationComponent>(0.01f);
	auto& input = InputManager::GetInstance();
	input.BindCommand(GameEngine::InputManager::InputKey::WASD, gameActor.get());
	m_Scene->Add(std::move(gameActor));

	//m_Scene->Add(std::move(gameObject2));

	gameActor = std::make_unique<GameActor>("PacmanFemale",3,400.f);
	gameActor->SetPosition(200.f, 200.f);
	gameActor->AddComponent<TextureComponent>("PacmanFemale.png");
	//gameObject2->SetParent(gameObject.get());
	//gameObject2->AddComponent<RotationComponent>(0.03f,false);
	input.BindCommand(GameEngine::InputManager::InputKey::DPAD, gameActor.get(),0);

	m_Scene->Add(std::move(gameActor));

	//scene.Add(std::move(gameObject2));

	//gameObject = std::make_unique<GameObject>("IMGUI");
	//gameObject->AddComponent<IMGUIComponent>();
	//scene.Add(std::move(gameObject));

	return *m_Scene;
}
