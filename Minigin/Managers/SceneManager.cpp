#include "SceneManager.h"
#include "Minigin/Subjects/GameObject.h"

void GameEngine::SceneManager::SetCurrentScene(int sceneId)
{
    m_CurrentSceneId = sceneId;
}
void GameEngine::SceneManager::AddScene(int sceneId, std::unique_ptr<Scene>&& scene)
{
    m_Scenes[sceneId] = std::move(scene);
}
void GameEngine::SceneManager::Update()
{
    if(m_CurrentSceneId != -1) m_Scenes[m_CurrentSceneId]->Update();
}

void GameEngine::SceneManager::Render()
{
    if(m_CurrentSceneId != -1) m_Scenes[m_CurrentSceneId]->Render();
}

