#include "FormationObserver.h"

#include <iostream>

#include "DataStructs.h"
#include "Game components/FormationComponent.h"

int FormationObserver::m_CurrentStage = 0;
int FormationObserver::m_CurrentEnemiesSetOut = 0;
int FormationObserver::m_CurrentEnemiesGotInFormation = 0;
int FormationObserver::m_NrOfStages;

void FormationObserver::Notify([[maybe_unused]] GameEngine::Subject* subject, int event,
    [[maybe_unused]] GameEngine::EventData* eventData)
{
    switch (static_cast<GameEvent>(event))
    {
    case GameEvent::died:
    {
        if (m_CurrentEnemiesSetOut)
        {
            --m_CurrentEnemiesSetOut;
            std::cout << "Enemy died. Current enemies set out:" << m_CurrentEnemiesSetOut << '\n';
        }
    }
    break;
    case GameEvent::gotInFormation:
    {
        ++m_CurrentEnemiesGotInFormation;
        std::cout << "Enemy got in formation. Current enemies in formation:" << m_CurrentEnemiesGotInFormation << '\n';
    }
    break;
    default: break;
    }
    if (m_CurrentEnemiesGotInFormation == m_CurrentEnemiesSetOut && m_CurrentEnemiesGotInFormation != 0)
    {
        m_CurrentEnemiesGotInFormation = 0;
        m_CurrentEnemiesSetOut = 0;
        ++m_CurrentStage;
        if (m_CurrentStage == m_NrOfStages)
        {
            m_NrOfStages = -1;
            FormationComponent::ToggleUpdate();
        }
    }
}
