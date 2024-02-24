#include "Scene.h"
#include "GameObject.h"

#include <algorithm>
#include <sstream>
#include <iomanip>
#include "TextComponent.h"
#include "Time.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	auto& time = Time::GetInstance();
	m_FpsUpdateCounter += time.GetElapsed();
	for(auto& object : m_objects)
	{
		if (object->GetName() == "FPSCounter" && m_FpsUpdateCounter >= m_FpsUpdateRate)
		{
			m_FpsUpdateCounter -= m_FpsUpdateRate;
			const float fpsCounter{ 1.f / time.GetElapsed() };
			std::stringstream stream{};
			stream << std::fixed << std::setprecision(1) << fpsCounter; 
			object->GetComponent<TextComponent>()->SetText(stream.str());
		}
		object->Update();
	}
	if(m_FpsUpdateCounter >= m_FpsUpdateRate) m_FpsUpdateCounter -= m_FpsUpdateRate;
}

void dae::Scene::FixedUpdate()
{ 
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

