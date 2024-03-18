#pragma once
#include <memory>

namespace GameEngine {
	class Controller final
	{
	public:
		explicit Controller(unsigned int controllerIdx);
		~Controller();
		Controller(const Controller& other) = delete;
		Controller(Controller&& other) = delete;
		Controller& operator=(const Controller& other) = delete;
		Controller& operator=(Controller&& other) = delete;

		void ProcessControllerInput();

		bool IsDpadUpKeyDown() const;
		bool IsDpadDownKeyDown() const;
		bool IsDpadLeftKeyDown() const;
		bool IsDpadRightKeyDown() const;

		bool IsDpadUpKeyUp() const;
		bool IsDpadDownKeyUp() const;
		bool IsDpadLeftKeyUp() const;
		bool IsDpadRightKeyUp() const;
	private:
		class XInput;
		std::unique_ptr<XInput> m_pXInput;
	};
}


