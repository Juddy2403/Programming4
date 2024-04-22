#pragma once
#include "Component.h"
#include "Singleton.h"

namespace GameEngine
{
    class CollisionManager final : public Singleton<CollisionManager>
    {
    public:
        void AddCollisionComponent(GameEngine::CollisionComponent* collisionComponent);
        void RemoveCollisionComponent(GameEngine::CollisionComponent* collisionComponent);
        void CheckCollisions() const;
    private:
        friend class Singleton<CollisionManager>;
        CollisionManager() = default;
        
        std::vector<GameEngine::CollisionComponent*> m_CollisionComponents{};
    };
}
