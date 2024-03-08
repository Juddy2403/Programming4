#pragma once
#include "Component.h"
#include <imgui_plot.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL_stdinc.h>
#include <vector>

class vector;
namespace GameEngine {
	
	class IMGUIComponent : public Component
	{
	private:
		void CalculateArrayEx1(int nrOfSamples = 10);
		ImGui::PlotConfig m_PlotConf{};
		std::vector<float> m_AvgTimes{};
		enum class PlotUpdateStage {
			noUpdate,
			clearButton,
			showTextMsg,
			updatePlot
		};
		PlotUpdateStage m_PlotUpdateStage{ PlotUpdateStage::noUpdate };
		void UpdatePlot1(int nrOfSamples);
	public:
		explicit IMGUIComponent(GameObject* gameObj);

		virtual void Render() override;
	};
}