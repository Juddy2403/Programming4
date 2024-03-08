#include "IMGUIComponent.h"

#pragma warning( disable : 4244 )

#include <chrono>
#include <numeric>
#include <set>

GameEngine::IMGUIComponent::IMGUIComponent(GameObject* gameObj) : Component(gameObj)
{
	//CalculateArrayEx1();
}

void GameEngine::IMGUIComponent::CalculateArrayEx1(int nrOfSamples)
{
	constexpr int arrSize{ 67108864 };
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
	m_AvgTimes.clear();
	for (auto& timesVec : timesRecorded)
	{
		float timeAverageVal = std::accumulate(++timesVec.begin(), --timesVec.end(), 0.f);
		m_AvgTimes.push_back(timeAverageVal / ((nrOfSamples - 2) * 1000.0));
	}
}

void GameEngine::IMGUIComponent::Render() 
{
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);

	static int nrOfSamples{ 10 };
	ImGui::InputInt("# samples:", &nrOfSamples);
	switch (m_PlotUpdateStage)
	{
	case PlotUpdateStage::noUpdate:
		if (ImGui::Button("Trash the cache"))
			m_PlotUpdateStage = PlotUpdateStage::clearButton;
		break;
	case PlotUpdateStage::clearButton:
		m_PlotUpdateStage = PlotUpdateStage::showTextMsg;
		break;
	case PlotUpdateStage::showTextMsg:
		ImGui::Text("Wait for it..");
		m_PlotUpdateStage = PlotUpdateStage::updatePlot;
		break;
	case PlotUpdateStage::updatePlot:
		UpdatePlot1(nrOfSamples);
		m_PlotUpdateStage = PlotUpdateStage::noUpdate;
		break;
	}

	ImGui::Plot("plot1", m_PlotConf);

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameEngine::IMGUIComponent::UpdatePlot1(int nrOfSamples)
{
	constexpr size_t buf_size = 12;
	static float x_data[buf_size] = { 1,2,4,8,16,32,64,128,256,512,1024 };

	ImU32 color = ImColor(0, 255, 0);
	static uint32_t selection_start = 0, selection_length = 0;

	CalculateArrayEx1(nrOfSamples);
	m_PlotConf.values.xs = x_data;
	m_PlotConf.values.ys = m_AvgTimes.data();
	m_PlotConf.values.count = buf_size;
	m_PlotConf.values.color = color;
	m_PlotConf.scale.min = 0;
	m_PlotConf.scale.max = m_AvgTimes[0] + 1; // for y axis
	m_PlotConf.tooltip.show = true;
	m_PlotConf.grid_x.show = true;
	m_PlotConf.grid_x.size = buf_size;
	m_PlotConf.grid_x.subticks = buf_size;
	m_PlotConf.grid_y.show = true;
	m_PlotConf.grid_y.size = 0.5f;
	m_PlotConf.grid_y.subticks = 5;
	m_PlotConf.selection.show = true;
	m_PlotConf.selection.start = &selection_start;
	m_PlotConf.selection.length = &selection_length;
	m_PlotConf.frame_size = ImVec2(buf_size * 25, 200);
	m_PlotConf.line_thickness = 2.f;
}
