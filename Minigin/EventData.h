#pragma once

namespace GameEngine
{
    struct EventData {};
    struct CollisionData : EventData
    {
        GameObject* pOtherCollider;
    };
}
