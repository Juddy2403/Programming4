#pragma once
#include <SDL_render.h>
#include <utility>
#include <vector>

namespace GameEngine
{
    class SpriteComponent;
}
class RotatingSprite final
{
public:
    explicit RotatingSprite(int nrOfCols);

    RotatingSprite(const RotatingSprite& other) = delete;
    RotatingSprite(RotatingSprite&& other) noexcept = delete;
    RotatingSprite& operator=(const RotatingSprite& other) = delete;
    RotatingSprite& operator=(RotatingSprite&& other) noexcept = delete;
    ~RotatingSprite() = default;

    std::pair<int,SDL_RendererFlip> GetColFlipPair(int index) const { return m_ColFlipPairs[index]; }
private:
    void InitColFlipPairs(int nrOfCols);
    std::vector<std::pair<int,SDL_RendererFlip>> m_ColFlipPairs;
};
