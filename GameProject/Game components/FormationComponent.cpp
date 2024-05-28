#include "FormationComponent.h"
#include <iostream>
#include "Subjects/GameObject.h"
#include "Managers/TimeManager.h"

bool FormationComponent::m_IsUpdating = false;
float FormationComponent::m_Offset = 0;
int FormationComponent::m_Direction = 1;
bool FormationComponent::m_DoesExist = false;
FormationComponent::FormationComponent(GameEngine::GameObject* gameObj):
    Component(gameObj)
{
    if (!m_DoesExist) m_DoesExist = true;
    else
    {
        std::cerr << "FormationComponent already exists in the scene\n";
        gameObj->RemoveComponent<FormationComponent>();
    }
}
void FormationComponent::Update()
{
    if(m_IsUpdating)
    {
        m_Offset += m_Direction * m_Speed * GameEngine::TimeManager::GetElapsed();
        if(m_Offset <= -m_OffsetLimit) m_Direction = 1;
        else if(m_Offset >= m_OffsetLimit) m_Direction = -1;
    }
}
float FormationComponent::GetOffset() 
{
    if(m_DoesExist) return m_Offset;
    throw std::runtime_error("FormationComponent does not exist in the scene");
}
