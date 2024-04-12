#include "BackgroundComponent.h"

#include <iostream>

#include "GameObject.h"
#include "Renderer.h"
#include "TimeManager.h"

BackgroundComponent::BackgroundComponent(GameEngine::GameObject* gameObject, GameEngine::TextureComponent* textureComponent, int speed):
    Component(gameObject),
    m_TextureComponent(textureComponent),
    m_Speed(speed)
{}
void BackgroundComponent::Update()
{
    m_CurrentY += static_cast<int>(m_Speed * GameEngine::TimeManager::GetElapsed());
    if (m_CurrentY >= m_TextureComponent->GetDestRect().h)
    {
        m_CurrentY -= m_TextureComponent->GetDestRect().h;
    }
    GetGameObjParent()->SetPosition(0, static_cast<float>(m_CurrentY));
}
void BackgroundComponent::Render()
{
    SDL_Rect destRect = m_TextureComponent->GetDestRect();
    destRect.y = m_CurrentY - destRect.h;
    //Rebdering a second texture for the loop effect
    GameEngine::Renderer::GetInstance().RenderTexture(*m_TextureComponent->GetTexture(), m_TextureComponent->GetSourceRect(), destRect);
}
