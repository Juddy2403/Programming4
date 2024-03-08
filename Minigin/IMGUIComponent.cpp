#include "IMGUIComponent.h"

#pragma warning( disable : 4244 )

#include <chrono>
#include <numeric>
#include <set>

GameEngine::IMGUIComponent::IMGUIComponent(GameObject* gameObj) : Component(gameObj)
{
	//CalculateArrayEx1();
	m_AvgTimes = std::make_unique<std::vector<float>>();
}

void GameEngine::IMGUIComponent::CalculateArrayEx1() 
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
	delete[] arr;
	for (auto& timesVec : timesRecorded)
	{
		float timeAverageVal = std::accumulate(++timesVec.begin(), --timesVec.end(), 0.f);
		m_AvgTimes->push_back(timeAverageVal / ((nrOfSamples - 2) * 1000.0));
	}
}

void GameEngine::IMGUIComponent::Render() 
{

	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	//ImGuiIO& io = ImGui::GetIO();

	
	constexpr size_t buf_size = 11;
	static float x_data[buf_size] = {1,2,4,8,16,32,64,128,256,512,1024};

	ImU32 color = ImColor(0, 255, 0);
	static uint32_t selection_start = 0, selection_length = 0;

	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	// Create a button

	if (ImGui::Button("Click Me")) {
		//ImGui::BulletText("Double-click on title bar to collapse window.");
		
		// Draw first plot with multiple sources
		CalculateArrayEx1();
		conf.values.xs = x_data;
		conf.values.ys = m_AvgTimes->data();
		conf.values.count = buf_size;
		conf.values.color = color;
		conf.scale.min = 0;
		conf.scale.max = m_AvgTimes.get()->at(0) + 1 ; // for y axis
		conf.tooltip.show = true;
		conf.grid_x.show = true;
		conf.grid_x.size = 11;
		conf.grid_x.subticks = 11;
		conf.grid_y.show = true;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 5;
		conf.selection.show = true;
		conf.selection.start = &selection_start;
		conf.selection.length = &selection_length;
		conf.frame_size = ImVec2(buf_size * 25, 200);
		conf.line_thickness = 2.f;
	}
	ImGui::Plot("plot1", conf);

	static int inputVar{ 10 };
	// Input integer variable from the user
	ImGui::InputInt("Input Variable", &inputVar);
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
