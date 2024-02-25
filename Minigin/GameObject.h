#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include <string>

class Component;
namespace dae
{
	class GameObject final
	{
	private:
		Transform m_Transform{};
		std::vector<std::shared_ptr<Component>> m_Components{};
		std::string m_Name{};
	public:
		void Update();
		void Render() const;

		void SetPosition(float x, float y);
		glm::vec3 GetPosition() const;
		std::string GetName() const;

		GameObject() = default;
		GameObject(std::string name);
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Component Handling
		template<typename T, typename... Types>
		void AddComponents(const T& var1, const Types&... var2) {
			(void)var1; //this is stupid
			static_assert(std::is_base_of<Component, T>::value, "T must be a subclass of Component");
			std::shared_ptr<T> component = std::make_shared<T>();
			m_Components.push_back(component);
			if constexpr (sizeof...(var2) > 0)
				AddComponents(var2...);
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
		void RemoveComponent() {
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

	};
}
