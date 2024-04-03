#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
#include "Scene.h"

namespace GameEngine
{
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		//void FixedUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unique_ptr<Scene> m_Scene;
	};
}
