#include "ScoreComponent.h"

#include "Game observers/ScoreManager.h"
ScoreComponent::ScoreComponent(GameEngine::GameObject* gameObj, GameEngine::TextComponent* textComp)
: Component(gameObj), m_TextComponent(textComp)
{
    m_LastScore = ScoreManager::GetPlayerScore(0); //TODO: Get player id from game object
    m_TextComponent->SetText(std::to_string(m_LastScore));
}

void ScoreComponent::Update()
{
    const auto currentScore = ScoreManager::GetPlayerScore(0); //TODO: Get player id from game object
    if(currentScore != m_LastScore)
    {
        m_LastScore = currentScore;
        m_TextComponent->SetText(std::to_string(m_LastScore));
    }
}
