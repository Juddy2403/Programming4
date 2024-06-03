#include "Scene.h"
#include "Subjects/GameObject.h"
#include "IObserver.h"
#include <algorithm>
#include "Managers/CollisionManager.h"
#include "Managers/InputManager.h"
#include "Managers/TimeManager.h"

using namespace GameEngine;

//#define CHECK_COLLISION_RECTS

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

GameObject* Scene::AddObject(std::unique_ptr<GameObject>&& object)
{
    m_GameObjects.emplace_back(std::move(object));
    return m_GameObjects.back().get();
}

IObserver* GameEngine::Scene::AddObserver(int message, std::unique_ptr<IObserver>&& observer, GameObject* gameObj)
{
    if (gameObj != nullptr)
        gameObj->AddObserver(message, m_Observers.emplace_back(std::move(observer)).get());
    else m_Observers.emplace_back(std::move(observer));
    return m_Observers.back().get();
}

void Scene::Remove(const std::unique_ptr<GameObject>& object)
{
    std::erase(m_GameObjects, object);
}

void Scene::RemoveAll()
{
    m_GameObjects.clear();
}

void Scene::Update()
{
    bool areElemsToErase = false;
    for (const auto& object : m_GameObjects)
    {
        if (!object->IsDestroyed()) object->Update();
        else areElemsToErase = true;
    }
    if (areElemsToErase) RemoveDestroyedObjects();
    CollisionManager::CheckCollisions();
}

void Scene::Render() const
{
    for (const auto& object : m_GameObjects)
    {
        object->Render();
    }
    #ifdef CHECK_COLLISION_RECTS
    CollisionManager::RenderCollisionRects();
    #endif
}

void Scene::RemoveDestroyedObjects()
{
    const auto range = std::ranges::remove_if(m_GameObjects,
        [](const auto& obj) {
            return obj->IsDestroyed();
        });
    // Erase the destroyed objects from the vector
    m_GameObjects.erase(range.begin(), range.end());
}
