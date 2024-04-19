#include "PlayerComponent.h"
#include "GameObject.h"
#include "TimeManager.h"


ActorDataComponent::ActorDataComponent(GameEngine::GameObject* gameObject, int health):
    Component(gameObject),
    m_Health(health)
{}
void ActorDataComponent::IncreaseScore(int value)
{
    m_Score += value;
    GetGameObjParent()->Notify(GameEngine::GameEvent::scoreIncreased,
        static_cast<int>(GameEngine::ObserverIdentifier::score));
}
void ActorDataComponent::Hit()
{
    --m_Health;
    GetGameObjParent()->Notify(GameEngine::GameEvent::playerDied, static_cast<int>(GameEngine::ObserverIdentifier::health));
}

RotatingSpriteComponent::RotatingSpriteComponent(GameEngine::GameObject* gameObj):
    SpriteComponent(gameObj)
{}

RotatingSpriteComponent::RotatingSpriteComponent(GameEngine::GameObject* gameObj,
    const std::string& filename):
    SpriteComponent(gameObj, filename)
{}

RotatingSpriteComponent::RotatingSpriteComponent(GameEngine::GameObject* gameObj,
    const std::shared_ptr<GameEngine::Texture2D>& texture):
    SpriteComponent(gameObj, texture)
{}
void RotatingSpriteComponent::Update()
{
    if(!m_IsActive) return;
    m_CurrentTimeElapsed += GameEngine::TimeManager::GetElapsed();
    if (m_CurrentTimeElapsed < m_SpriteInfo.m_TimeInterval) return;

    m_IsColIncreasing ? ++m_SpriteInfo.m_CurrentCol : --m_SpriteInfo.m_CurrentCol;

    if (m_SpriteInfo.m_CurrentCol == m_SpriteInfo.m_NrOfCols - 1)
    {
        m_IsColIncreasing = false;
        m_FlipMode = m_FlipMode == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_VERTICAL;
    }
    else if (m_SpriteInfo.m_CurrentCol == 0)
    {
        m_IsColIncreasing = true;
        ++m_SpriteInfo.m_CurrentRow %= m_SpriteInfo.m_NrOfRows;
        m_FlipMode = m_FlipMode == SDL_FLIP_HORIZONTAL ? static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) : SDL_FLIP_NONE;
    }

    UpdateSrcRect();
    m_CurrentTimeElapsed -= m_SpriteInfo.m_TimeInterval;
}

