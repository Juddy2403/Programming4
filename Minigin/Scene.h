#pragma once
#include <string>
#include <memory>
#include <vector>

namespace GameEngine
{
	class GameObject;
	class Scene final
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		GameObject* Add(std::unique_ptr<GameObject>&& object);
		void Remove(std::unique_ptr<GameObject>&& object);
		void RemoveAll();

		void Update();
		//void FixedUpdate();
		void Render() const;
		void RemoveDestroyedObjects();

		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		float m_FpsUpdateCounter{};
		const float m_FpsUpdateRate{ 0.5f };
		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;

		static unsigned int m_idCounter; 
	};

}
