#pragma once
#include <memory>

namespace GameEngine {
	class Controller
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
		XInput* m_pXInput; //will resource leak if its a unique ptr
		//should ask why it prob has smth to do with the unique_ptr<Controller> inside InputManager
	};
}


