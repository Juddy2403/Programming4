#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <thread>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Time.h"
//using namespace std::chrono;

SDL_Window* g_window{};
constexpr duration<float, std::milli> g_MsPerUpdate{ 100.f / 16.f };

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

GameEngine::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

GameEngine::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}
void GameEngine::Minigin::Run(const std::function<void()>& load)
{
	SDL_GL_SetSwapInterval(1); //for a steady framerate of 160 using Vsync

	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time = Time::GetInstance();

	//float lag = 0.f;
	bool doContinue = true;
	while (doContinue)
	{
		time.Update();
		//lag += time.GetElapsed();
		//while(lag >= g_MsPerUpdate.count())
		//{
		//	//fixed update happens here (physics and networking)
		//	lag -= g_MsPerUpdate.count();
		//}

		sceneManager.Update();
		//LATE UPDATE HERE (for eg camera)
		// 
		//should pass lag/msPerUpdate to Render
		renderer.Render();
		doContinue = input.ProcessInput();

		//const duration<float,std::milli> sleep_time = time.GetCurrent() + g_MsPerUpdate - high_resolution_clock::now();
		//if(sleep_time.count() > 0)
		//std::this_thread::sleep_for(sleep_time);
	}
}
