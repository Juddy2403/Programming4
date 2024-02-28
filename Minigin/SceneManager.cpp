#include "SceneManager.h"
#include "Scene.h"

void GameEngine::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

//void GameEngine::SceneManager::FixedUpdate()
//{
//
//}

void GameEngine::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

GameEngine::Scene& GameEngine::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
