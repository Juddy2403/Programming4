#pragma once
#include <memory>

namespace GameEngine {
	class Controller final
	{
	public:
		enum class InputKey {
			DPAD_UP   = 513,
			DPAD_LEFT = 514,
			DPAD_DOWN = 515,
			DPAD_RIGHT= 516,
			X = 517,
			Y = 518,
			A = 519,
			B = 520
		};

		explicit Controller(unsigned int controllerIdx);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void ProcessControllerInput();

		bool IsKeyDown(int inputKey);

		bool IsKeyUp(int inputKey);

	private:
		class XInput;
		std::unique_ptr<XInput> m_pXInput;
	};
}


