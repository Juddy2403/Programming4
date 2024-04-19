#include "Component.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "TimeManager.h"
#include <numbers>

#pragma warning( disable : 4244 )

using namespace GameEngine;

#pragma region Component
GameObject* Component::GetGameObjParent() const
{
    return m_pParent;
}

bool Component::IsDestroyed() const
{
    return m_IsDestroyed;
}

void Component::SetDestroyedFlag()
{
    m_IsDestroyed = true;
}

Component::Component(GameObject* gameObj):
    m_pParent{ gameObj }
{}
#pragma endregion

#pragma region Texture Component

TextureComponent::TextureComponent(GameObject* gameObj): Component(gameObj)
{}

TextureComponent::TextureComponent(GameObject* gameObj, const std::string& filename) :
    Component(gameObj)
{
    SetTexture(filename);
}

void TextureComponent::InitRects()
{
    m_SrcRect.x = 0;
    m_SrcRect.y = 0;
    m_SrcRect.w = m_Texture->GetSize().x;
    m_SrcRect.h = m_Texture->GetSize().y;

    m_DestRect = m_SrcRect;
}
TextureComponent::TextureComponent(GameObject* gameObj, const std::shared_ptr<Texture2D>& texture) :
    Component(gameObj)
{
    SetTexture(texture);
}

void TextureComponent::Render()
{
    if (m_Texture != nullptr)
    {
        const auto pos = GetGameObjParent()->GetPosition();
        m_DestRect.x = static_cast<int>(pos.x);
        m_DestRect.y = static_cast<int>(pos.y);
        if(m_RotationAngle != 0 || m_FlipMode != SDL_FLIP_NONE)
            Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, m_DestRect, m_RotationAngle, m_RotationCenter, m_FlipMode);
        else
            Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, m_DestRect);
    }
}
Texture2D* TextureComponent::GetTexture() const
{
    return m_Texture.get();
}

void TextureComponent::SetTexture(const std::string& filename)
{ //TODO: refactor the shared pointer into a unique ptr
    m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
    InitRects();
}

void TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
{
    m_Texture = texture;
    InitRects();
}

#pragma endregion

#pragma region Text Component
TextComponent::TextComponent(GameObject* gameObj, std::shared_ptr<Font> font, const std::string& text) : Component(gameObj)
{
    if (font) SetFont(font);
    SetText(text);
}
void TextComponent::SetText(const std::string& text)
{
    if (m_Text != text)
    {
        m_Text = text;
        m_NeedsUpdate = true;
    }
}

void TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
    assert(font);
    if (font) m_Font = font;
}

void TextComponent::Update()
{
    if (m_NeedsUpdate && GetGameObjParent()->CheckIfComponentExists<TextureComponent>())
    {
        constexpr SDL_Color color = { 255,255,255,255 }; // only white text is supported now
        const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
        if (surf == nullptr)
        {
            throw std::runtime_error(std::string("Render  text failed: ") + SDL_GetError());
        }
        auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
        if (texture == nullptr)
        {
            throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
        }
        SDL_FreeSurface(surf);
        GetGameObjParent()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
        m_NeedsUpdate = false;
    }
}

#pragma endregion

#pragma region Sprite component
SpriteComponent::SpriteComponent(GameObject* gameObj): TextureComponent(gameObj) {}
SpriteComponent::SpriteComponent(GameObject* gameObj, const std::string& filename):
    TextureComponent(gameObj, filename) {}
SpriteComponent::SpriteComponent(GameObject* gameObj, const std::shared_ptr<Texture2D>& texture) :
    TextureComponent(gameObj, texture) {}

void SpriteComponent::UpdateSrcRect()
{
    m_SrcRect = m_SpriteInfo.GetSrcRect();
    if (m_SrcRect.w == 0 || m_SrcRect.h == 0)
    {
        m_DestRect.w *= m_Scale;
        m_DestRect.h *= m_Scale;
    }
    else
    {
        m_DestRect.w = m_SrcRect.w * m_Scale;
        m_DestRect.h = m_SrcRect.h * m_Scale;
    }
}
void SpriteComponent::Update()
{
    if(!m_IsActive) return;
    m_CurrentTimeElapsed += TimeManager::GetElapsed();
    if (m_CurrentTimeElapsed >= m_SpriteInfo.m_TimeInterval)
    {
        ++m_SpriteInfo.m_CurrentCol %= m_SpriteInfo.m_NrOfCols;
        if (m_SpriteInfo.m_CurrentCol == 0) ++m_SpriteInfo.m_CurrentRow %= m_SpriteInfo.m_NrOfRows;
        UpdateSrcRect();
        m_CurrentTimeElapsed -= m_SpriteInfo.m_TimeInterval;
    }
}
#pragma endregion

// #pragma region IMGUI Component
// IMGUIComponent::IMGUIComponent(GameObject* gameObj) : Component(gameObj)
// {
// 	m_IntPlotUpdateInfo->buttonMsg = "Trash the cache";
// 	m_IntPlotUpdateInfo->color = ImColor(0, 255, 0);
//
// 	m_GameObjPlotUpdateInfo->buttonMsg = "Trash the cache with GameObject3D";
// 	m_GameObjPlotUpdateInfo->color = ImColor(0, 0, 255);
//
// 	m_AltGameObjPlotUpdateInfo->buttonMsg = "Trash the cache with GameObject3DAlt";
// 	m_AltGameObjPlotUpdateInfo->color = ImColor(255, 0, 0);
// }
//
// void IMGUIComponent::Render()
// {
// 	//Manage exercise 1 graph
// 	RenderExercise1();
//
// 	//Manage exercise 2 graph
// 	RenderExercise2();
// }
//
// void IMGUIComponent::RenderExercise1()
// {
// 	ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_None);
// 	static int nrOfSamples{ 10 };
// 	ImGui::InputInt("# samples:", &nrOfSamples);
//
// 	ManagePlotUpdateStages<int>(m_IntPlotUpdateInfo.get(), nrOfSamples);
// 	ImGui::Plot("Int plot", *m_IntPlotUpdateInfo->plotConfig);
// 	ImGui::End();
// }
//
// void IMGUIComponent::RenderExercise2()
// {
// 	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_None);
//
// 	static int nrOfSamples{ 100 };
// 	ImGui::InputInt("# samples:", &nrOfSamples);
//
// 	ManagePlotUpdateStages<GameObject3D>(m_GameObjPlotUpdateInfo.get(), nrOfSamples);
// 	ImGui::Plot("GameObj plot", *m_GameObjPlotUpdateInfo->plotConfig);
//
// 	ManagePlotUpdateStages<GameObject3DAlt>(m_AltGameObjPlotUpdateInfo.get(), nrOfSamples);
// 	ImGui::Plot("AltGameObj plot", *m_AltGameObjPlotUpdateInfo->plotConfig);
//
// 	if (!m_GameObjPlotUpdateInfo->avgTime.empty() && !m_AltGameObjPlotUpdateInfo->avgTime.empty())
// 	{
// 		RenderCombinedConf();
// 		ImGui::Plot("Combined plot", *m_CombinedPlotConf);
// 	}
//
// 	ImGui::End();
// }
//
// void IMGUIComponent::RenderCombinedConf()
// {
// 	ImGui::Text("Combined:");
//
// 	static const float* y_data[] = { m_AltGameObjPlotUpdateInfo->avgTime.data(), m_GameObjPlotUpdateInfo->avgTime.data() };
// 	static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 0, 255) };
//
// 	*m_CombinedPlotConf = *m_GameObjPlotUpdateInfo->plotConfig;
// 	m_CombinedPlotConf->values.color = 0;
// 	m_CombinedPlotConf->values.colors = colors;
// 	m_CombinedPlotConf->values.ys = nullptr;
// 	m_CombinedPlotConf->values.ys_list = y_data;
// 	m_CombinedPlotConf->values.ys_count = 2;
// 	m_CombinedPlotConf->scale.max = std::max(*std::max_element(m_GameObjPlotUpdateInfo->avgTime.begin(), m_GameObjPlotUpdateInfo->avgTime.end()),
// 		*std::max_element(m_AltGameObjPlotUpdateInfo->avgTime.begin(), m_AltGameObjPlotUpdateInfo->avgTime.end())) + 1;
// }
// #pragma endregion

// #pragma region FPS Component
// const float FPSComponent::m_FpsUpdateRate = 1.f;
//
// FPSComponent::FPSComponent(GameObject* gameObj, TextComponent* textComponent) :Component(gameObj),
// m_TextComponent{ textComponent }
// {
// }
//
// void FPSComponent::Update()
// {
// 	auto& time = TimeManager::GetInstance();
// 	m_FpsUpdateCounter += time.GetElapsed();
// 	++m_FramesSinceUpdate;
// 	if (m_FpsUpdateCounter >= m_FpsUpdateRate)
// 	{
// 		m_FPS = m_FramesSinceUpdate / m_FpsUpdateCounter;
// 		if (m_TextComponent != nullptr) m_TextComponent->SetText(std::format("{:.1f} FPS", m_FPS));
// 		m_FramesSinceUpdate = 0;
// 		m_FpsUpdateCounter -= m_FpsUpdateRate;
// 	}
// }
// #pragma endregion
//
// #pragma region Rotation Component
// RotationComponent::RotationComponent(GameObject* gameObj, float velocity,
// 	bool isRotatingClockwise) :
// 	Component(gameObj),
// 	m_IsRotatingClockwise{ isRotatingClockwise },
// 	m_Velocity{ velocity }
// {
// }
//
// void RotationComponent::Update()
// {
// 	if (GetGameObjParent()->GetParent() != nullptr)
// 	{
// 		constexpr float fullRotation{ 2 * static_cast<float>(std::numbers::pi) };
//
// 		if (m_IsRotatingClockwise)
// 		{
// 			m_Angle += TimeManager::GetElapsed() * m_Velocity;
// 			if (m_Angle >= fullRotation) m_Angle -= fullRotation;
// 		}
// 		else
// 		{
// 			m_Angle -= TimeManager::GetElapsed() * m_Velocity;
// 			if (m_Angle <= fullRotation) m_Angle += fullRotation;
// 		}
// 		GetGameObjParent()->GetLocalTransform().SetRotation(m_Angle);
// 		GetGameObjParent()->SetPositionIsDirty();
// 	}
// }
// #pragma endregion
