#pragma once
#include "Component.h"

namespace GameEngine
{
    class CollisionManager final
    {
    public:
        CollisionManager(const CollisionManager& other) = delete;
        CollisionManager(CollisionManager&& other) noexcept = delete;
        CollisionManager& operator=(const CollisionManager& other) = delete;
        CollisionManager& operator=(CollisionManager&& other) noexcept = delete;
        
        static void AddCollisionComponent(GameEngine::CollisionComponent* collisionComponent);
        static void RemoveCollisionComponent(GameEngine::CollisionComponent* collisionComponent);
        static void CheckCollisions();
        static void RenderCollisionRects();
        
        CollisionManager() = delete;
        ~CollisionManager() = delete;
    private:
        static std::vector<GameEngine::CollisionComponent*> m_CollisionComponents;
    };
}
