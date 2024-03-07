#pragma once
#include "Component.h"

namespace GameEngine {

	class IMGUIComponent : public Component
	{
	private:
		std::vector<float> m_AvgTimes{};
	public:
		explicit IMGUIComponent(GameObject* gameObj);

		virtual void Render() const override;
	};
}