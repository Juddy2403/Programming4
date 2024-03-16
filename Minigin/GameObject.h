#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <string>
#include <concepts>
#include <algorithm>

namespace GameEngine
{
	class Component;
	template<typename T>
	concept ComponentType = std::is_base_of<Component, T>::value;
	class GameObject 
	{
	private:
		std::vector<std::unique_ptr<Component>> m_Components{};
		std::string m_Name{};
		bool m_IsDestroyed{ false };

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		//Scene graph functions
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(GameObject* child);

		//Transform members
		Transform m_WorldTransform{};
		Transform m_LocalTransform{};
		bool m_IsPositionDirty{ true };
	public:
		void Update();
		void Render() const;
		std::string GetName() const;

		bool IsDestroyed() const;
		void SetDestroyedFlag();
		void RemoveDestroyedObjects();

		//Scene graph functions
		GameObject* GetParent() const;
		void SetParent(GameObject* parent, bool keepWorldPosition = true);
		int GetChildCount() const;
		GameObject* GetChildAt(int index);

		//Transform functions
		void SetLocalTransform(const Transform& transform);
		Transform& GetLocalTransform();
		Transform GetWorldTransform();
		void UpdateWorldTransform();
		void SetPositionIsDirty();

		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const MathHelper::Vector3& pos);
		MathHelper::Vector3 GetPosition() ;

		GameObject() = default;
		GameObject(std::string name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Component Handling

		template<ComponentType T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			m_Components.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
			return dynamic_cast<T*>(m_Components.back().get());
		}
		template<ComponentType T>
		T* AddComponent()
		{
			m_Components.push_back(std::make_unique<T>(this));
			return dynamic_cast<T*>(m_Components.back().get());
		}

		template<ComponentType T>
		T* GetComponent() const {
			for (const auto& componentPtr : m_Components) {
				auto ptr = dynamic_cast<T*>(componentPtr.get());
				if (ptr) return ptr;
			}
			return nullptr; // Component not found
		}

		template<ComponentType T>
		void RemoveComponent() {
			const auto ret = std::ranges::remove_if(m_Components, [](const auto& elem) {
				return (dynamic_cast<T*>(elem.get()));
				});
			m_Components.erase(ret.begin(), ret.end());
		}

		template<ComponentType T>
		bool CheckIfComponentExists() const {
			return std::ranges::find_if(m_Components, [](const auto& elem) {
				return (dynamic_cast<T*>(elem.get()));
				}
			) != m_Components.end();
		}
#pragma endregion


	};
}
