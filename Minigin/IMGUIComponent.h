#pragma once
#include "Component.h"
#include <imgui_plot.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL_stdinc.h>
#include <vector>

namespace GameEngine {

	class IMGUIComponent : public Component
	{
	private:
		void CalculateArrayEx1();
		ImGui::PlotConfig conf{};
		std::unique_ptr<std::vector<float>> m_AvgTimes;

	public:
		explicit IMGUIComponent(GameObject* gameObj);

		virtual void Render() override;
	};
}