#pragma once
#include <string>
#include <memory>
#include <vector>

namespace GameEngine
{
	class IObserver;
	class GameObject;
	class Scene final
	{
	public:
		GameObject* AddObject(std::unique_ptr<GameObject>&& object);
		IObserver* AddObserver(int message,std::unique_ptr<IObserver>&& observer,GameObject* gameObj);
		void Remove(const std::unique_ptr<GameObject>& object);
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
		Scene& operator=(Scene&& other) noexcept = delete;
		
	private: 
		std::string m_Name;
		std::vector<std::unique_ptr<IObserver>> m_Observers;
		std::vector<std::unique_ptr<GameObject>> m_GameObjects;

	};

}
