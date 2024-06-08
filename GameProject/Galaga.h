#pragma once
#include <memory>

#include "Managers/Singleton.h"
enum class SceneId;
enum class GameMode;
namespace GameEngine {class Scene;}
class Galaga final : public GameEngine::Singleton<Galaga>
{
public:
    ~Galaga() = default;
    Galaga(const Galaga& other) = delete;
    Galaga(Galaga&& other) noexcept = delete;
    Galaga& operator=(const Galaga& other) = delete;
    Galaga& operator=(Galaga&& other) noexcept = delete;

    void LoadScenes();
    void SetGameMode(GameMode mode);
    static constexpr int volume = 50;
private:
    friend class Singleton<Galaga>;
    Galaga() = default;

    bool m_HasGameModeBeenSet{false};
    GameMode m_CurrentGameMode;
    SceneId m_CurrentScene;
    std::unique_ptr<GameEngine::Scene> LoadLevelOne();
    std::unique_ptr<GameEngine::Scene> LoadStartScreen();
};
