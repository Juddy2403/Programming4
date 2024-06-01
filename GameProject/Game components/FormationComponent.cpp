#include "FormationComponent.h"
#include <iostream>

#include "Enemy components/EnemyComponent.h"
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
    if(m_Scene)
    {
        if(m_CurrentStage < m_Stages)
        {
            if(!m_LoadedStage)
            {
                for(auto& obj : m_Formation[m_CurrentStage])
                {
                    m_CurrentlyLoadedEnemies.push_back(m_Scene->AddObject(std::move(obj)));
                    for(auto& observer : m_Observers)
                    {
                        m_Scene->AddObserver(-1, observer, m_CurrentlyLoadedEnemies.back());
                    }
                }
                m_LoadedStage = true;
            }
            else
            {
                for (auto& obj : m_CurrentlyLoadedEnemies)
                {
                    glm::ivec2 pos = obj->GetIntPosition();
                    if(obj->GetComponent<EnemyComponent>()->GetFormationPosition() != pos) return;
                    ++m_CurrentStage;
                }
            }
        }
        else
        {
            m_CurrentlyLoadedEnemies.clear();
            m_Scene = nullptr;
            m_IsUpdating = true;
        }
    }
    if(m_IsUpdating)
    {
        m_Offset += m_Direction * m_Speed * GameEngine::TimeManager::GetElapsed();
        if(m_Offset <= -m_OffsetLimit) m_Direction = 1;
        else if(m_Offset >= m_OffsetLimit) m_Direction = -1;
    }
}
void FormationComponent::LoadFormation(GameEngine::Scene* scene, std::vector<std::vector<std::unique_ptr<GameEngine::GameObject>>>&& formation,
    const std::vector<GameEngine::IObserver*>& observers)
{
    m_Scene = scene;
    m_Formation = std::move(formation);
    m_Stages = m_Formation.size();
    m_Observers = observers;
}
float FormationComponent::GetOffset() 
{
    if(m_DoesExist) return m_Offset;
    throw std::runtime_error("FormationComponent does not exist in the scene");
}
