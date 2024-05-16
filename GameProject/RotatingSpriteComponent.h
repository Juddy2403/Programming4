#pragma once
#include "Components/Component.h"

class RotatingSpriteComponent final : public GameEngine::Component
{
public:
    explicit RotatingSpriteComponent(GameEngine::GameObject* gameObj, int nrOfCols);

    RotatingSpriteComponent(const RotatingSpriteComponent& other) = delete;
    RotatingSpriteComponent(RotatingSpriteComponent&& other) noexcept = delete;
    RotatingSpriteComponent& operator=(const RotatingSpriteComponent& other) = delete;
    RotatingSpriteComponent& operator=(RotatingSpriteComponent&& other) noexcept = delete;
    ~RotatingSpriteComponent() override = default;

    std::pair<int,SDL_RendererFlip> GetColFlipPair(int index) const { return m_ColFlipPairs[index]; }
private:
    void InitColFlipPairs(int nrOfCols);
    std::vector<std::pair<int,SDL_RendererFlip>> m_ColFlipPairs;
};
