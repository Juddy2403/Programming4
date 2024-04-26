#include "Scene.h"
#include "GameObject.h"
#include "IObserver.h"
#include <algorithm>
#include <future>

#include "CollisionManager.h"
#include "InputManager.h"
#include "DerivedSoundSystems.h"
#include "TimeManager.h"

using namespace GameEngine;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

GameObject* Scene::AddObject(std::unique_ptr<GameObject>&& object)
{
    m_GameObjects.emplace_back(std::move(object));
    return m_GameObjects.back().get();
}

IObserver* GameEngine::Scene::AddObserver(int message, std::unique_ptr<IObserver>&& observer, GameObject* gameObj)
{
    gameObj->AddObserver(message, m_Observers.emplace_back(std::move(observer)).get());
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
    //auto collisionFuture = std::async(&CollisionManager::CheckCollisions);
    CollisionManager::CheckCollisions();
    //ServiceLocator::GetSoundSystem().Update();
    for (const auto& object : m_GameObjects)
    {
        if (!object->IsDestroyed()) object->Update();
        else areElemsToErase = true;
    }
    //collisionFuture.get();
    if (areElemsToErase) RemoveDestroyedObjects();
}

void Scene::Render() const
{
    for (const auto& object : m_GameObjects)
    {
        object->Render();
    }
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
