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
	ManageIntPlotUpdateStages(nrOfSamples);
	ImGui::Plot("Int plot", *m_IntPlotConf);
	ImGui::End();
}

void GameEngine::IMGUIComponent::RenderExercise2()
{
	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);

	static int nrOfSamples{ 100 };
	ImGui::InputInt("# samples:", &nrOfSamples);

	ManageGameObjPlotUpdateStages(nrOfSamples);
	ImGui::Plot("GameObj plot", *m_GameObjPlotConf);

	ManageAltGameObjPlotUpdateStages(nrOfSamples);
	ImGui::Plot("AltGameObj plot", *m_AltGameObjPlotConf);

	if (!m_GameObjAvgTime.empty() && !m_AltGameObjAvgTime.empty())
	{
		ImGui::Text("Combined:");

		static const float* y_data[] = { m_AltGameObjAvgTime.data(), m_GameObjAvgTime.data()};
		static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 0, 255) };

		*m_CombinedPlotConf = *m_GameObjPlotConf;
		m_CombinedPlotConf->values.color = 0;
		m_CombinedPlotConf->values.colors = colors;
		m_CombinedPlotConf->values.ys = nullptr;
		m_CombinedPlotConf->values.ys_list = y_data;
		m_CombinedPlotConf->values.ys_count = 2;
		m_CombinedPlotConf->scale.max =std::max( *std::max_element(m_GameObjAvgTime.begin(), m_GameObjAvgTime.end()),
			*std::max_element(m_AltGameObjAvgTime.begin(), m_AltGameObjAvgTime.end())) + 1; // for y axis
		ImGui::Plot("Combined plot", *m_CombinedPlotConf);
	}

	ImGui::End();
}

void GameEngine::IMGUIComponent::ManageGameObjPlotUpdateStages(int nrOfSamples)
{
	switch (m_GameObjPlotUpdateStage)
	{
	case PlotUpdateStage::noUpdate:
		if (ImGui::Button("Trash the cache with GameObject3D"))
			m_GameObjPlotUpdateStage = PlotUpdateStage::clearButton;
		break;
	case PlotUpdateStage::clearButton:
		m_GameObjPlotUpdateStage = PlotUpdateStage::showTextMsg;
		break;
	case PlotUpdateStage::showTextMsg:
		ImGui::Text("Wait for it..");
		m_GameObjPlotUpdateStage = PlotUpdateStage::updatePlot;
		break;
	case PlotUpdateStage::updatePlot:
		UpdatePlot<GameObject3D>(*m_GameObjPlotConf, m_GameObjAvgTime,ImColor(0, 0, 255),nrOfSamples);
		m_GameObjPlotUpdateStage = PlotUpdateStage::noUpdate;
		break;
	}
}

void GameEngine::IMGUIComponent::ManageIntPlotUpdateStages(int nrOfSamples)
{
	switch (m_IntPlotUpdateStage)
	{
	case PlotUpdateStage::noUpdate:
		if (ImGui::Button("Trash the cache"))
			m_IntPlotUpdateStage = PlotUpdateStage::clearButton;
		break;
	case PlotUpdateStage::clearButton:
		m_IntPlotUpdateStage = PlotUpdateStage::showTextMsg;
		break;
	case PlotUpdateStage::showTextMsg:
		ImGui::Text("Wait for it..");
		m_IntPlotUpdateStage = PlotUpdateStage::updatePlot;
		break;
	case PlotUpdateStage::updatePlot:
		//UpdateIntPlot(nrOfSamples);
		UpdatePlot<int>(*m_IntPlotConf, m_IntAvgTime,ImColor(0, 255, 0), nrOfSamples);
		m_IntPlotUpdateStage = PlotUpdateStage::noUpdate;
		break;
	}
}

void GameEngine::IMGUIComponent::ManageAltGameObjPlotUpdateStages(int nrOfSamples)
{
	switch (m_AltGameObjPlotUpdateStage)
	{
	case PlotUpdateStage::noUpdate:
		if (ImGui::Button("Trash the cache with GameObject3DAlt"))
			m_AltGameObjPlotUpdateStage = PlotUpdateStage::clearButton;
		break;
	case PlotUpdateStage::clearButton:
		m_AltGameObjPlotUpdateStage = PlotUpdateStage::showTextMsg;
		break;
	case PlotUpdateStage::showTextMsg:
		ImGui::Text("Wait for it..");
		m_AltGameObjPlotUpdateStage = PlotUpdateStage::updatePlot;
		break;
	case PlotUpdateStage::updatePlot:
		UpdatePlot<GameObject3DAlt>(*m_AltGameObjPlotConf,m_AltGameObjAvgTime, ImColor(255, 0, 0), nrOfSamples);
		m_AltGameObjPlotUpdateStage = PlotUpdateStage::noUpdate;
		break;
	}
}


