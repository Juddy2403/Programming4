#include "InputManager.h"
#include <ranges>

bool GameEngine::InputManager::ProcessInput()
{
    if(!ProcessKeyboardInput()) return false;
    ProcessControllerInput();
    return true;
}


void GameEngine::InputManager::ProcessControllerInput()
{
    for (size_t i = 0; i < g_maxControllerCount; i++)
    {
        if (m_pControllers[i] == nullptr) continue;
        m_pControllers[i]->ProcessControllerInput();
        
        //TODO: perhaps create an event queue with the inputs received
        for (const auto& [inputKey, command] : m_pControllerCommands[i])
        {
            switch (command->ExecuteOnKeyState())
            {
            case ICommand::ExecuteOn::keyPressed:
                if (m_pControllers[i]->IsKeyPressed(inputKey))
                    command->Execute();
                break;
            case ICommand::ExecuteOn::keyUp:
                if (m_pControllers[i]->IsKeyUp(inputKey)) command->Execute();
                break;
            case ICommand::ExecuteOn::keyDown:
                if (m_pControllers[i]->IsKeyDown(inputKey)) command->Execute();
                break;
            }
        }
    }
}
bool GameEngine::InputManager::ProcessKeyboardInput()
{
    if(!m_pKeyboard->ProcessKeyboardInput()) return false;
        
    //TODO: perhaps create an event queue with the inputs received
    for (const auto& [inputKey, command] : m_pKeyboardCommands)
    {
        switch (command->ExecuteOnKeyState())
        {
        case ICommand::ExecuteOn::keyPressed:
            if (m_pKeyboard->IsKeyPressed(inputKey)) command->Execute();
            break;
        case ICommand::ExecuteOn::keyUp:
            if (m_pKeyboard->IsKeyUp(inputKey)) command->Execute();
            break;
        case ICommand::ExecuteOn::keyDown:
            if (m_pKeyboard->IsKeyDown(inputKey)) command->Execute();
            break;
        }
    }
    return true;
}

void GameEngine::InputManager::BindCommand(KeyboardInputKey inputKey, std::unique_ptr<ICommand>&& command)
{
    m_pKeyboardCommands[inputKey] = std::move(command);
}
void GameEngine::InputManager::BindCommand(ControllerInputKey inputKey, std::unique_ptr<ICommand>&& command, int controllerIdx)
{
    if (m_pControllers[controllerIdx] == nullptr)
        m_pControllers[controllerIdx] = std::make_unique<Controller>(controllerIdx);

    m_pControllerCommands[controllerIdx][inputKey] = std::move(command);
}

