#include "IMGUIComponent.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui_plot.h>
#include <SDL_stdinc.h>
#pragma warning( disable : 4244 )

#include <vector>
#include <chrono>
#include <numeric>
#include <set>

GameEngine::IMGUIComponent::IMGUIComponent(GameObject* gameObj): Component(gameObj)
{
	constexpr int arrSize{ 67108864 };
	constexpr int nrOfSamples{ 20 };
	int* arr = new int[arrSize];

	std::vector<std::set<long>> timesRecorded(11);

	for (size_t j = 0; j < nrOfSamples; j++)
	{
		int index{ -1 };
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			auto start_time = std::chrono::high_resolution_clock::now();

			for (int i = 0; i < arrSize; i += stepsize)
			{
				arr[i] *= 2;
			}
			auto end_time = std::chrono::high_resolution_clock::now();

			const auto total = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
			timesRecorded[++index].insert(total);
		}
	}
	for (auto& timesVec : timesRecorded)
	{
		float timeAverageVal = std::accumulate(++timesVec.begin(), --timesVec.end(), 0.f);
		m_AvgTimes.push_back(timeAverageVal / ((nrOfSamples - 2) * 1000.0));
	}
	
}

void GameEngine::IMGUIComponent::Render() const
{

	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();

	constexpr size_t buf_size = 11;
	static float x_data[11] = {1,2,4,8,16,32,64,128,256,512,1024};
	//static float y_data1[buf_size];
	//static float y_data2[buf_size];
	//static float y_data3[buf_size];


	/*constexpr float sampling_freq = 44100;
	constexpr float freq = 500;
	for (size_t i = 0; i < buf_size; ++i) {
		const float t = i / sampling_freq;
		x_data[i] = t;
		const float arg = 2 * M_PI * freq * t;
		y_data1[i] = sin(arg);
		y_data2[i] = y_data1[i] * -0.6 + sin(2 * arg) * 0.4;
		y_data3[i] = y_data2[i] * -0.6 + sin(3 * arg) * 0.4;
	}*/


	static const float* y_data[] = { m_AvgTimes.data() };
	static ImU32 colors[1] = { ImColor(0, 255, 0)};
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Example plot", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// Draw first plot with multiple sources
	ImGui::PlotConfig conf;
	conf.values.xs = x_data;
	conf.values.ys = m_AvgTimes.data();
	conf.values.count = buf_size;
	conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
	conf.values.ys_count = 1;
	conf.values.colors = colors;
	conf.scale.min = 0;
	conf.scale.max = 100;
	conf.tooltip.show = true;
	conf.grid_x.show = true;
	conf.grid_x.size = 40;
	conf.grid_x.subticks = 4;
	conf.grid_y.show = true;
	conf.grid_y.size = 0.5f;
	conf.grid_y.subticks = 5;
	conf.selection.show = true;
	conf.selection.start = &selection_start;
	conf.selection.length = &selection_length;
	conf.frame_size = ImVec2(buf_size*25, 200);
	ImGui::Plot("plot1", conf);

	// Draw second plot with the selection
	// reset previous values
	//conf.values.ys_list = nullptr;
	//conf.selection.show = false;
	//// set new ones
	//conf.values.ys = y_data3;
	//conf.values.offset = selection_start;
	//conf.values.count = selection_length;
	//conf.line_thickness = 2.f;
	//ImGui::Plot("plot2", conf);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
