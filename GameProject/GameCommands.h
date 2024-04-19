#pragma once
#include "TimeManager.h"
#include "ICommand.h"

class ShootBulletCommand final : public GameEngine::ICommand
{
public:
    ShootBulletCommand(const ShootBulletCommand& other) = delete;
    ShootBulletCommand(ShootBulletCommand&& other) noexcept = delete;
    ShootBulletCommand& operator=(const ShootBulletCommand& other) = delete;
    ShootBulletCommand& operator=(ShootBulletCommand&& other) noexcept = delete;
		
    explicit ShootBulletCommand(GameEngine::GameObject* actor);
    ~ShootBulletCommand() override = default;
    void Execute() override;
    [[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
private:
    const float m_ShootCooldown{ 1.f };
    std::chrono::high_resolution_clock::time_point m_Previous{ std::chrono::high_resolution_clock::now() };
    std::chrono::high_resolution_clock::time_point m_Current{};
    const int m_MaxShootCount{ 2 };
    int m_ShootsAvailable{ 2 };
};
