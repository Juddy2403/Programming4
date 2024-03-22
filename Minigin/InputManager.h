#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"
#include <forward_list>
#include <array>
#include <map>

namespace GameEngine
{
	constexpr size_t maxControllerCount{4};

	class Controller;
	class GameActor;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputKey {
			WASD,
			DPAD
		};

		void BindCommand(InputKey inputKey, GameActor* actor, int controllerIdx = -1);

		bool ProcessInput();
		void ProcessControllerInput();
		void ExecuteCommand();

		~InputManager() override = default;
	private:
		//Commands
		//InputManager();

		typedef std::unique_ptr<Command> CommandUnique;
		typedef std::map<InputKey, CommandUnique> CommandMap;

		std::map<InputKey, CommandUnique> m_pKeyboardCommands;
		std::array<CommandMap, maxControllerCount> m_pControllerCommands;

		std::array<std::unique_ptr<Controller>, maxControllerCount> m_pControllers;
	
	};

}
