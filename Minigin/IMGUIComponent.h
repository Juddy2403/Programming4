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

namespace GameEngine {

	class IMGUIComponent : public Component
	{
	private:

		std::unique_ptr<ImGui::PlotConfig> m_IntPlotConf{ std::make_unique< ImGui::PlotConfig>() };
		std::unique_ptr<ImGui::PlotConfig> m_GameObjPlotConf{ std::make_unique< ImGui::PlotConfig>() };
		std::unique_ptr<ImGui::PlotConfig> m_AltGameObjPlotConf{ std::make_unique< ImGui::PlotConfig>() };
		std::unique_ptr<ImGui::PlotConfig> m_CombinedPlotConf{ std::make_unique< ImGui::PlotConfig>() };

		std::vector<float> m_IntAvgTime;
		std::vector<float> m_GameObjAvgTime;
		std::vector<float> m_AltGameObjAvgTime;

		enum class PlotUpdateStage {
			noUpdate,
			clearButton,
			showTextMsg,
			updatePlot
		};
		PlotUpdateStage m_IntPlotUpdateStage{ PlotUpdateStage::noUpdate };
		PlotUpdateStage m_GameObjPlotUpdateStage{ PlotUpdateStage::noUpdate };
		PlotUpdateStage m_AltGameObjPlotUpdateStage{ PlotUpdateStage::noUpdate };

		void ManageIntPlotUpdateStages(int nrOfSamples);
		void ManageAltGameObjPlotUpdateStages(int nrOfSamples);
		void RenderExercise1();

		void ManageGameObjPlotUpdateStages(int nrOfSamples);

		template<typename T>
		void CalculateTimeAvg(int nrOfSamples, std::vector<float>& avgTimes)
		{
			constexpr int arrSize{ (std::is_same<T, int>::value) ? 67108864 : 10000000 };
			T* arr = new T[arrSize]{};
			std::vector<std::set<long>> timesRecorded(11);

			for (size_t j = 0; j < nrOfSamples; j++)
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
		void UpdatePlot(ImGui::PlotConfig& plotConf, std::vector<float>& avgTime, const ImU32& color, int nrOfSamples)
		{
			static constexpr size_t buf_size = 11;
			static float x_data[buf_size] = { 1,2,4,8,16,32,64,128,256,512,1024 };

			//ImU32 color = ImColor(0, 255, 0);
			static uint32_t selection_start = 0, selection_length = 0;
			CalculateTimeAvg<T>(nrOfSamples, avgTime);
			plotConf.values.xs = x_data;
			plotConf.values.ys = avgTime.data();
			plotConf.values.count = buf_size;
			plotConf.values.color = color;
			plotConf.scale.min = 0;
			plotConf.scale.max = *std::max_element(avgTime.begin(), avgTime.end()) + 1; // for y axis
			plotConf.tooltip.show = true;
			plotConf.grid_x.show = false;
			plotConf.grid_y.show = true;
			plotConf.selection.show = true;
			plotConf.selection.start = &selection_start;
			plotConf.selection.length = &selection_length;
			plotConf.frame_size = ImVec2(250, 150);
			plotConf.line_thickness = 2.f;
		}

	public:
		explicit IMGUIComponent(GameObject* gameObj);
		//void CalculateArray(int nrOfSamples, auto* arr, std::vector<float>& avgTimes);
		virtual void Render() override;
		void RenderExercise2();
	};
}