#pragma once
#include <memory>
namespace GameEngine {class Scene;}
class Galaga final 
{
public:
    Galaga() = default;
    ~Galaga() = default;
    Galaga(const Galaga& other) = delete;
    Galaga(Galaga&& other) noexcept = delete;
    Galaga& operator=(const Galaga& other) = delete;
    Galaga& operator=(Galaga&& other) noexcept = delete;

    void LoadScenes();
    static constexpr int volume = 50;
private:
    std::unique_ptr<GameEngine::Scene> LoadLevelOne();
};
