#pragma once
#include <memory>
#include "Singleton.h"
#include "../Scene.h"

namespace GameEngine
{

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void SetScene(std::unique_ptr<Scene>&& scene);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unique_ptr<Scene> m_Scene;
	};
}
