#pragma once
#include "Input/Command.h"
#include "Managers/TimeManager.h"

class ModeSelectionComp;
class ShootBulletCommand final : public GameEngine::Command
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
    const float m_ShootCooldown{ .5f };
    std::chrono::high_resolution_clock::time_point m_Previous{ std::chrono::high_resolution_clock::now() };
    std::chrono::high_resolution_clock::time_point m_Current{};
    const int m_MaxShootCount{ 2 };
    int m_ShootsAvailable{ 2 };
};

class SwitchModesCommand final : public GameEngine::Command
{
public:
    SwitchModesCommand(const SwitchModesCommand& other) = delete;
    SwitchModesCommand(SwitchModesCommand&& other) noexcept = delete;
    SwitchModesCommand& operator=(const SwitchModesCommand& other) = delete;
    SwitchModesCommand& operator=(SwitchModesCommand&& other) noexcept = delete;

    explicit SwitchModesCommand(GameEngine::GameObject* actor, bool movingUp);
    ~SwitchModesCommand() override = default;
    void Execute() override;
    [[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
private:
    ModeSelectionComp* m_ModeSelectionComp;
    bool m_IsMovingUp;
};

class SelectModeCommand final : public GameEngine::Command
{
public:
    SelectModeCommand(const SelectModeCommand& other) = delete;
    SelectModeCommand(SelectModeCommand&& other) noexcept = delete;
    SelectModeCommand& operator=(const SelectModeCommand& other) = delete;
    SelectModeCommand& operator=(SelectModeCommand&& other) noexcept = delete;

    explicit SelectModeCommand(GameEngine::GameObject* actor);
    ~SelectModeCommand() override = default;
    void Execute() override;
    [[nodiscard]] ExecuteOn ExecuteOnKeyState() const override;
private:
    ModeSelectionComp* m_ModeSelectionComp;
};



