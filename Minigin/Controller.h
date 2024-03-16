#pragma once
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#include <XInput.h>

namespace GameEngine {
	class Controller
	{
	private:
		XINPUT_STATE m_PreviousState{};
		XINPUT_STATE m_CurrentState{};
		unsigned int m_ControllerIdx{ 0 };
		unsigned int m_ButtonsPressedThisFrame{};
		unsigned int m_ButtonsReleasedThisFrame{};

	public:
		Controller(unsigned int controllerIdx);
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;
		virtual ~Controller() = default;

		void ProcessControllerInput();
		bool IsDownThisFrame(unsigned int button) const;
		bool IsUpThisFrame(unsigned int button) const;
		bool IsPressed(unsigned int button) const;

	};
}


