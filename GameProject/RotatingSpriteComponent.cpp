#include "RotatingSpriteComponent.h"

#include "TimeManager.h"

RotatingSpriteComponent::RotatingSpriteComponent(GameEngine::GameObject* gameObj, int nrOfCols):
    Component(gameObj)
{
    InitColFlipPairs(nrOfCols);
}

void RotatingSpriteComponent::InitColFlipPairs(int nrOfCols)
{
    bool isColIncreasing = true;
    int col = 0;
    SDL_RendererFlip flipMode = SDL_FLIP_NONE;
    m_ColFlipPairs.emplace_back(col, SDL_FLIP_NONE);

    for (int i = 0; i < nrOfCols * 4; ++i)
    {
        isColIncreasing ? ++col : --col;

        if (col == nrOfCols - 1)
        {
            isColIncreasing = false;
            flipMode = flipMode == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_VERTICAL;
        }
        else if (col == 0)
        {
            isColIncreasing = true;
            flipMode = flipMode == SDL_FLIP_HORIZONTAL ? static_cast<SDL_RendererFlip>(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) : SDL_FLIP_NONE;
        }
        m_ColFlipPairs.emplace_back(col, flipMode);
    }
}
