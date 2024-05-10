#include "Component.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL_ttf.h>
#include <stdexcept>
#include "TimeManager.h"
#include <numbers>

#include "CollisionManager.h"
#include "EventData.h"
#include "IObserver.h"

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
        if (m_RotationAngle != 0 || m_FlipMode != SDL_FLIP_NONE)
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
    if (!m_IsActive) return;
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

#pragma region Collision component

CollisionComponent::CollisionComponent(GameObject* gameObj,SDL_Rect* collisionRect):
    Component(gameObj),
    m_CollisionRect(collisionRect)
{
    CollisionManager::AddCollisionComponent(this);
}
const SDL_Rect& CollisionComponent::GetCollisionRect() const
{
    return *m_CollisionRect;
}
bool CollisionComponent::IsColliding(CollisionComponent* other) const
{
    return SDL_HasIntersection(m_CollisionRect, other->m_CollisionRect);
}
void CollisionComponent::CollidedWith(CollisionComponent* other) const
{
    CollisionData data;
    data.pOtherCollider = other->GetGameObjParent();
    GetGameObjParent()->NotifyAll(GameEvent::collision,&data);
}

void CollisionComponent::Update()
{
    m_CollisionRect->x = GetGameObjParent()->GetPosition().x;
    m_CollisionRect->y = GetGameObjParent()->GetPosition().y;
}
CollisionComponent::~CollisionComponent()
{
    CollisionManager::RemoveCollisionComponent(this);
}

#pragma endregion

