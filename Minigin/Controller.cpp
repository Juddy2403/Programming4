#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <XInput.h>
#include "Controller.h"
#include <iostream>

class GameEngine::Controller::XInput
{
private:
	unsigned int m_ControllerIdx{ 0 };
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
public:
	XInput(unsigned int controllerIdx): m_ControllerIdx{controllerIdx}{
	/*	DWORD result = XInputGetState(0, nullptr);
		if (result != ERROR_SUCCESS) {
			std::cout << "Cannot get XInput state! \n";
		}*/
	}

	XInput(const XInput& other) = delete;
	XInput(XInput&& other) = delete;
	XInput& operator=(const XInput& other) = delete;
	XInput& operator=(XInput&& other) = delete;

	void ProcessControllerInput() {
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIdx, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}
	bool IsDownThisFrame(unsigned int button) const {
		return m_ButtonsPressedThisFrame & button;
	}
	bool IsUpThisFrame(unsigned int button) const {
		return m_ButtonsReleasedThisFrame & button;
	}
	bool IsPressed(unsigned int button) const {
		return m_CurrentState.Gamepad.wButtons & button;
	}
};

GameEngine::Controller::Controller(unsigned int controllerIdx):
	m_pXInput{std::make_unique<XInput>(controllerIdx)}
{
}

GameEngine::Controller::~Controller(){}

void GameEngine::Controller::ProcessControllerInput()
{
	m_pXInput->ProcessControllerInput();
}

bool GameEngine::Controller::IsKeyDown(int inputKey)
{
	InputKey inputEnum = static_cast<InputKey>(inputKey);
	switch (inputEnum)
	{
	case InputKey::DPAD_UP:
		return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP);
		break;
	case InputKey::DPAD_DOWN:
		return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN);
		break;
	case InputKey::DPAD_RIGHT:
		return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case InputKey::DPAD_LEFT:
		return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	}
	return false;
}

bool GameEngine::Controller::IsKeyUp(int inputKey)
{
	InputKey inputEnum = static_cast<InputKey>(inputKey);
	switch (inputEnum)
	{
	case InputKey::DPAD_UP:
		return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_UP);
		break;
	case InputKey::DPAD_DOWN:
		return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_DOWN);
		break;
	case InputKey::DPAD_RIGHT:
		return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT);
		break;
	case InputKey::DPAD_LEFT:
		return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_LEFT);
		break;
	}
	return false;
}
