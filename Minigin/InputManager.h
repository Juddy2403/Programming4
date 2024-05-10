#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"
#include "KeyboardInput.h"
#include <array>
#include <unordered_map>

namespace GameEngine
{
    class KeyboardInput;
    class GameActor;
    class InputManager final : public Singleton<InputManager>
    {
    public:
        InputManager() = default;
        InputManager(const InputManager& other) = delete;
        InputManager(InputManager&& other) noexcept = delete;
        InputManager& operator=(const InputManager& other) = delete;
        InputManager& operator=(InputManager&& other) noexcept = delete;
        ~InputManager() override = default;

        bool ProcessInput();
        void ProcessControllerInput();
        bool ProcessKeyboardInput();

        void BindCommand(KeyboardInputKey inputKey, std::unique_ptr<Command>&& command);
        void BindCommand(ControllerInputKey inputKey, std::unique_ptr<Command>&& command, int controllerIdx);

    private:
        //Commands
        typedef std::unique_ptr<Command> CommandUnique;
        typedef std::unordered_map<KeyboardInputKey,CommandUnique> KeyboardCommandMap;
        typedef std::unordered_map<ControllerInputKey,CommandUnique> ControllerCommandMap;
        KeyboardCommandMap m_pKeyboardCommands;
        std::array<ControllerCommandMap, g_maxControllerCount> m_pControllerCommands;

        std::array<std::unique_ptr<Controller>, g_maxControllerCount> m_pControllers;
        std::unique_ptr<KeyboardInput> m_pKeyboard{std::make_unique<KeyboardInput>()};

    };
}
