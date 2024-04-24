#include "CollisionManager.h"
using namespace GameEngine;

std::vector<GameEngine::CollisionComponent*> CollisionManager::m_CollisionComponents{};

void CollisionManager::AddCollisionComponent(GameEngine::CollisionComponent* collisionComponent)
{
    m_CollisionComponents.emplace_back(collisionComponent);
}
void CollisionManager::RemoveCollisionComponent(GameEngine::CollisionComponent* collisionComponent)
{
    std::erase(m_CollisionComponents, collisionComponent);
}
void CollisionManager::CheckCollisions() 
{
    const size_t size = m_CollisionComponents.size();
    for (size_t first = 0; first < size - 1; ++first)
    {
        for (size_t second = first + 1; second < size; ++second)
        {
            if (m_CollisionComponents[first]->IsColliding(m_CollisionComponents[second]))
            {
                m_CollisionComponents[first]->CollidedWith(m_CollisionComponents[second]);
                m_CollisionComponents[second]->CollidedWith(m_CollisionComponents[first]);
            }
        }
    }
}
