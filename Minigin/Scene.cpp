#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include "TextComponent.h"
#include "Time.h"

using namespace GameEngine;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

GameObject* Scene::Add(std::unique_ptr<GameObject>&& object)
{
	m_GameObjects.emplace_back(std::move(object));
	return m_GameObjects.back().get();
}

void Scene::Remove(std::unique_ptr<GameObject>&& object)
{
	m_GameObjects.erase(std::remove(m_GameObjects.begin(), m_GameObjects.end(), object), m_GameObjects.end());
}

void Scene::RemoveAll()
{
	m_GameObjects.clear();
}

void Scene::Update()
{
	bool areElemsToErase = false;
	for(auto& object : m_GameObjects)
	{
		if (!object->IsDestroyed()) object->Update();
		else areElemsToErase = true;
	}
	if(areElemsToErase) RemoveDestroyedObjects();
}

//void GameEngine::Scene::FixedUpdate()
//{ 
//}

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

