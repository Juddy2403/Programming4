#pragma once
#include "Singleton.h"
#include "Command.h"
#include "Controller.h"
#include <forward_list>
#include <array>
#include <map>
#include <SDL.h>
#include <unordered_map>

namespace GameEngine
{
	template<typename T>
	concept CompmandType = std::is_base_of<Command, T>::value;

	constexpr size_t maxControllerCount{ 4 };

	class Controller;
	class GameActor;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputKey {
			DPAD_UP    = static_cast<int>(Controller::InputKey::DPAD_UP),
			DPAD_LEFT  = static_cast<int>(Controller::InputKey::DPAD_LEFT),
			DPAD_DOWN  = static_cast<int>(Controller::InputKey::DPAD_DOWN),
			DPAD_RIGHT = static_cast<int>(Controller::InputKey::DPAD_RIGHT),
			W = SDL_SCANCODE_W,
			A = SDL_SCANCODE_A,
			S = SDL_SCANCODE_S,
			D = SDL_SCANCODE_D,
			Z = SDL_SCANCODE_Z
		};

		bool ProcessInput();
		void ProcessControllerInput();


		~InputManager() override = default;

		template<CompmandType T>
		void BindCommand(InputKey inputKey, GameActor* actor, int controllerIdx = -1)
		{
			if (controllerIdx >= 0) {
				//adding a controller ptr if its needed
				if (m_pControllers[controllerIdx] == nullptr)
					m_pControllers[controllerIdx] = std::make_unique<Controller>(controllerIdx);

				m_pControllerCommands[controllerIdx][inputKey] = std::make_unique<T>(actor);
			}
			else m_pKeyboardCommands[inputKey] = std::make_unique<T>(actor);

		}

	private:
		//Commands
		//InputManager();

		//typedef std::unordered_map<InputKey, glm::vec2> InputKeyDirectionMap;
		//const InputKeyDirectionMap m_InputKeyDirections{
		//	 {InputKey::W,			glm::vec2(0, -1)},
		//	 {InputKey::A,			glm::vec2(-1, 0)},
		//	 {InputKey::S,			glm::vec2(0, 1)},
		//	 {InputKey::D,			glm::vec2(1, 0)},
		//	 {InputKey::DPAD_UP,    glm::vec2(0, -1)},
		//	 {InputKey::DPAD_LEFT,  glm::vec2(-1, 0)},
		//	 {InputKey::DPAD_DOWN,  glm::vec2(0, 1)},
		//	 {InputKey::DPAD_RIGHT, glm::vec2(1, 0)}
		//};

		typedef std::unique_ptr<Command> CommandUnique;
		typedef std::map<InputKey, CommandUnique> CommandMap;

		std::map<InputKey, CommandUnique> m_pKeyboardCommands;
		std::array<CommandMap, maxControllerCount> m_pControllerCommands;

		std::array<std::unique_ptr<Controller>, maxControllerCount> m_pControllers;

		void ProcessControllerKey(const size_t& i, const InputKey& inputKey);

		void ExecuteCommands();

	};

}
