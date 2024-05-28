#include "TextureComponent.h"

#include "../Managers/ResourceManager.h"
#include "../Renderable/Renderer.h"
#include "Minigin/Renderable/Texture2D.h"
#include "Minigin/Subjects/GameObject.h"

using namespace GameEngine;
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
        const auto pos = GetGameObjParent()->GetIntPosition();
        m_DestRect.x = static_cast<int>(pos.x);
        m_DestRect.y = static_cast<int>(pos.y);
        if (m_RotationAngle >= 0  || m_RotationAngle <= 0 || m_FlipMode != SDL_FLIP_NONE)
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