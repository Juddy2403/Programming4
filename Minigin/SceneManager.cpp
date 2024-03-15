#include "SceneManager.h"

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
	return *m_Scene;
}
