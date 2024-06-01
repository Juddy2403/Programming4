#include "FormationObserver.h"

#include "Game components/FormationComponent.h"

int FormationObserver::m_CurrentStage = 0;
int FormationObserver::m_CurrentEnemiesSetOut = 0;
int FormationObserver::m_CurrentEnemiesGotInFormation = 0;
int FormationObserver::m_NrOfStages;

void FormationObserver::Notify([[maybe_unused]] GameEngine::Subject* subject, GameEngine::GameEvent event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    switch (event)
    {
    case GameEngine::GameEvent::died:
    {
        if (m_CurrentEnemiesSetOut) --m_CurrentEnemiesSetOut;
    }
        break;
    case GameEngine::GameEvent::gotInFormation:
    {
        ++m_CurrentEnemiesGotInFormation;
    }
        break;
    default: break;
    }
    if(m_CurrentEnemiesGotInFormation == m_CurrentEnemiesSetOut && m_CurrentEnemiesGotInFormation != 0)
    {
        m_CurrentEnemiesGotInFormation = 0;
        m_CurrentEnemiesSetOut = 0;
        ++m_CurrentStage;
        if(m_CurrentStage == m_NrOfStages)
        {
            m_NrOfStages = -1;
            FormationComponent::ToggleUpdate();
        }
    }
}
