#pragma once
#include "Component.h"
#include <imgui_plot.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <SDL_stdinc.h>
#include <vector>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <set>

struct TransformM
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 };
};

class GameObject3D
{
public:
	TransformM transform;
	int ID;
};
class GameObject3DAlt
{
public:
	TransformM* transform{};
	int ID;

	~GameObject3DAlt() { delete transform; }
};
enum class PlotUpdateStage {
	noUpdate,
	clearButton,
	showTextMsg,
	updatePlot
};

struct PlotUpdateInfo{
	//PlotUpdateInfo() = default;
	PlotUpdateStage plotStage{ PlotUpdateStage::noUpdate };
	std::string buttonMsg{};
	std::unique_ptr<ImGui::PlotConfig> plotConfig{ std::make_unique< ImGui::PlotConfig>() };
	std::vector<float> avgTime{};
	ImU32 color{};
};

namespace GameEngine {

	class IMGUIComponent final : public Component
	{
	private:
		std::unique_ptr<PlotUpdateInfo> m_IntPlotUpdateInfo{std::make_unique<PlotUpdateInfo>()};
		std::unique_ptr<PlotUpdateInfo> m_GameObjPlotUpdateInfo{ std::make_unique<PlotUpdateInfo>() };
		std::unique_ptr<PlotUpdateInfo> m_AltGameObjPlotUpdateInfo{ std::make_unique<PlotUpdateInfo>() };
		std::unique_ptr<ImGui::PlotConfig> m_CombinedPlotConf{ std::make_unique< ImGui::PlotConfig>() };

		void RenderExercise1();
		void RenderExercise2();

		void RenderCombinedConf();

		template<typename T>
		void CalculateTimeAvg(int nrOfSamples, std::vector<float>& avgTimes)
		{
			constexpr int arrSize{ (std::is_same<T, int>::value) ? 67108864 : 10000000 };
			T* arr = new T[arrSize]{};
			std::vector<std::set<long>> timesRecorded(11);

			for (int j = 0; j < nrOfSamples; j++)
			{
				int index{ -1 };
				for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
				{
					auto start_time = std::chrono::high_resolution_clock::now();

					for (int i = 0; i < arrSize; i += stepsize)
					{
						if constexpr (std::is_same<T, int>::value) {
							arr[i] *= 2;
						}
						else if constexpr (std::is_same<T, GameObject3D>::value || std::is_same<T, GameObject3DAlt>::value) {
							arr[i].ID *= 2;
						}

					}
					auto end_time = std::chrono::high_resolution_clock::now();

					const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
					timesRecorded[++index].insert(total);
				}

			}
			delete[] arr;
			avgTimes.clear();
			for (auto& timesVec : timesRecorded)
			{
				float timeAverageVal = std::accumulate(++timesVec.begin(), --timesVec.end(), 0.f);
				avgTimes.push_back(timeAverageVal / (nrOfSamples - 2) / 100.f);
			}
		}

		template<typename T>
		void UpdatePlot(PlotUpdateInfo* plotUpdateInfo, int nrOfSamples)
		{
			static constexpr size_t buf_size = 11;
			static float x_data[buf_size] = { 1,2,4,8,16,32,64,128,256,512,1024 };

			//ImU32 color = ImColor(0, 255, 0);
			static uint32_t selection_start = 0, selection_length = 0;
			CalculateTimeAvg<T>(nrOfSamples, plotUpdateInfo->avgTime);
			plotUpdateInfo->plotConfig->values.xs = x_data;
			plotUpdateInfo->plotConfig->values.ys = plotUpdateInfo->avgTime.data();
			plotUpdateInfo->plotConfig->values.count = buf_size;
			plotUpdateInfo->plotConfig->values.color = plotUpdateInfo->color;
			plotUpdateInfo->plotConfig->scale.min = 0;
			plotUpdateInfo->plotConfig->scale.max = *std::max_element(plotUpdateInfo->avgTime.begin(), plotUpdateInfo->avgTime.end()) + 1; // for y axis
			plotUpdateInfo->plotConfig->tooltip.show = true;
			plotUpdateInfo->plotConfig->grid_x.show = false;
			plotUpdateInfo->plotConfig->grid_y.show = true;
			plotUpdateInfo->plotConfig->selection.show = true;
			plotUpdateInfo->plotConfig->selection.start = &selection_start;
			plotUpdateInfo->plotConfig->selection.length = &selection_length;
			plotUpdateInfo->plotConfig->frame_size = ImVec2(250, 150);
			plotUpdateInfo->plotConfig->line_thickness = 2.f;
		}

		template<typename T>
		void ManagePlotUpdateStages(PlotUpdateInfo* plotUpdateInfo,int nrOfSamples)
		{
			switch (plotUpdateInfo->plotStage)
			{
			case PlotUpdateStage::noUpdate:
				if (ImGui::Button(plotUpdateInfo->buttonMsg.c_str()))
					plotUpdateInfo->plotStage = PlotUpdateStage::clearButton;
				break;
			case PlotUpdateStage::clearButton:
				plotUpdateInfo->plotStage = PlotUpdateStage::showTextMsg;
				break;
			case PlotUpdateStage::showTextMsg:
				ImGui::Text("Wait for it..");
				plotUpdateInfo->plotStage = PlotUpdateStage::updatePlot;
				break;
			case PlotUpdateStage::updatePlot:
				UpdatePlot<T>(plotUpdateInfo, nrOfSamples);
				plotUpdateInfo->plotStage = PlotUpdateStage::noUpdate;
				break;
			}
		}

	public:
		explicit IMGUIComponent(GameObject* gameObj);
		//void CalculateArray(int nrOfSamples, auto* arr, std::vector<float>& avgTimes);
		virtual void Render() override;
	};
}