#include "Controller.h"
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <XInput.h>

class GameEngine::Controller::XInput
{
private:
	unsigned int m_ControllerIdx{ 0 };
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ButtonsPressedThisFrame{};
	unsigned int m_ButtonsReleasedThisFrame{};
public:
	XInput(unsigned int controllerIdx): m_ControllerIdx{controllerIdx}{}
	~XInput() = default;
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

GameEngine::Controller::~Controller()
{
	m_pXInput.release();
}

void GameEngine::Controller::ProcessControllerInput()
{
	m_pXInput->ProcessControllerInput();
}

bool GameEngine::Controller::IsDpadUpKeyDown() const
{
	return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_UP);
}

bool GameEngine::Controller::IsDpadDownKeyDown() const
{
	return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_DOWN);
}

bool GameEngine::Controller::IsDpadLeftKeyDown() const
{
	return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_LEFT);
}

bool GameEngine::Controller::IsDpadRightKeyDown() const
{
	return m_pXInput->IsDownThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT);
}

bool GameEngine::Controller::IsDpadUpKeyUp() const
{
	return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_UP);
}

bool GameEngine::Controller::IsDpadDownKeyUp() const
{
	return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_DOWN);
}

bool GameEngine::Controller::IsDpadLeftKeyUp() const
{
	return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_LEFT);
}

bool GameEngine::Controller::IsDpadRightKeyUp() const
{
	return m_pXInput->IsUpThisFrame(XINPUT_GAMEPAD_DPAD_RIGHT);
}

