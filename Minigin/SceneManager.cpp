#include "SceneManager.h"
#include "GameObject.h"

void GameEngine::SceneManager::Update()
{
    m_Scene->Update();
}

void GameEngine::SceneManager::Render()
{
    m_Scene->Render();

}

void GameEngine::SceneManager::SetScene(std::unique_ptr<Scene>&& scene)
{
    // m_Scene.reset(std::move(scene).get());
    m_Scene = std::move(scene);
}
