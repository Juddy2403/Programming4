#include "IMGUIComponent.h"

#pragma warning( disable : 4244 )

GameEngine::IMGUIComponent::IMGUIComponent(GameObject* gameObj) : Component(gameObj)
{}

void GameEngine::IMGUIComponent::Render() 
{
	ImGui::NewFrame();

	//Manage exercise 1 graph
	RenderExercise1();

	//Manage exercise 2 graph
	RenderExercise2();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GameEngine::IMGUIComponent::RenderExercise1()
{
	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
	static int nrOfSamples{ 10 };
	ImGui::InputInt("# samples:", &nrOfSamples);
	m_IntPlotUpdateInfo->buttonMsg = "Trash the cache";
	m_IntPlotUpdateInfo->color = ImColor(0, 255, 0);
	ManagePlotUpdateStages<int>(m_IntPlotUpdateInfo.get(), nrOfSamples);
	ImGui::Plot("Int plot", *m_IntPlotUpdateInfo->plotConfig);
	ImGui::End();
}

void GameEngine::IMGUIComponent::RenderExercise2()
{
	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);

	static int nrOfSamples{ 100 };
	ImGui::InputInt("# samples:", &nrOfSamples);

	m_GameObjPlotUpdateInfo->buttonMsg = "Trash the cache with GameObject3D";
	m_GameObjPlotUpdateInfo->color = ImColor(0, 0, 255);
	ManagePlotUpdateStages<GameObject3D>(m_GameObjPlotUpdateInfo.get(), nrOfSamples);
	ImGui::Plot("GameObj plot", *m_GameObjPlotUpdateInfo->plotConfig);

	m_AltGameObjPlotUpdateInfo->buttonMsg = "Trash the cache with GameObject3DAlt";
	m_AltGameObjPlotUpdateInfo->color = ImColor(255, 0, 0);
	ManagePlotUpdateStages<GameObject3DAlt>(m_AltGameObjPlotUpdateInfo.get(), nrOfSamples);
	ImGui::Plot("AltGameObj plot", *m_AltGameObjPlotUpdateInfo->plotConfig);

	if (!m_GameObjPlotUpdateInfo->avgTime.empty() && !m_AltGameObjPlotUpdateInfo->avgTime.empty())
	{
		UpdateCombinedConf();
		ImGui::Plot("Combined plot", *m_CombinedPlotConf);
	}

	ImGui::End();
}

void GameEngine::IMGUIComponent::UpdateCombinedConf()
{
	ImGui::Text("Combined:");

	static const float* y_data[] = { m_AltGameObjPlotUpdateInfo->avgTime.data(), m_GameObjPlotUpdateInfo->avgTime.data() };
	static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 0, 255) };

	*m_CombinedPlotConf = *m_GameObjPlotUpdateInfo->plotConfig;
	m_CombinedPlotConf->values.color = 0;
	m_CombinedPlotConf->values.colors = colors;
	m_CombinedPlotConf->values.ys = nullptr;
	m_CombinedPlotConf->values.ys_list = y_data;
	m_CombinedPlotConf->values.ys_count = 2;
	m_CombinedPlotConf->scale.max = std::max(*std::max_element(m_GameObjPlotUpdateInfo->avgTime.begin(), m_GameObjPlotUpdateInfo->avgTime.end()),
		*std::max_element(m_AltGameObjPlotUpdateInfo->avgTime.begin(), m_AltGameObjPlotUpdateInfo->avgTime.end())) + 1;
}


