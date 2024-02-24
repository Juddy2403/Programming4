#pragma once
#include <memory>
#include "Transform.h"
#include "Component.h"
#include <vector>

class Component;
namespace dae
{
	//class Texture2D;
	// todo: this should become final.
	class GameObject final
	{
	private:
		Transform m_Transform{};
		// todo: mmm, every gameobject has a texture? Is that correct? - should be part of a texture component 
		//std::shared_ptr<Texture2D> m_texture{};
		std::vector<std::shared_ptr<Component>> m_Components{};
	public:
		void Update(float elapsedSec);
		void Render() const;

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;

#pragma region Component Handling
		template<typename T, typename... Args>
		void AddComponent(Args&&... args) {
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			std::shared_ptr<T> component = std::make_shared<T>(std::forward<Args>(args)...);
			m_Components.push_back(component);
		}
		template<typename T>
		std::shared_ptr<T> GetComponent() const {
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			for (const auto& componentPtr : m_Components) {
				if (std::shared_ptr<T> desiredComponent = std::dynamic_pointer_cast<T>(componentPtr)) 
				{
					return desiredComponent;
				}
			}
			return nullptr; // Component not found
		}
		template<typename T>
		void RemoveComponent()  {
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			for (auto it = m_Components.begin(); it != m_Components.end(); ++it) {
				if (std::shared_ptr<T> desiredComponent = std::dynamic_pointer_cast<T>(*it)) {
					m_Components.erase(it);
					return;
				}
			}
		}
		template<typename T>
		bool CheckIfComponentExists() const {
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			for (const auto& componentPtr : m_Components) {
				if (std::dynamic_pointer_cast<T>(componentPtr) != nullptr) 
					return true;
			}
			return false; // Component not found
		}
#pragma endregion

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;


	};
}
