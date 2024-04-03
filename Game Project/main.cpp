#pragma once

//including vld
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include <SDL.h>
//#define STEAM_ACTIVE
#include "AchievementsManager.h"
#include "Minigin.h"
#include "SceneManager.h"
#include <iostream>

using namespace GameEngine;


void load()
{
	SceneManager::GetInstance().CreateScene("Demo");
}

int main(int, char* []) {
#ifdef STEAM_ACTIVE
	if (!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	else
		std::cout << "Successfully initialized steam." << std::endl;
	AchievementsManager::GetInstance().Init();
#endif

	Minigin engine("../Data/");
	engine.Run(load);

#ifdef STEAM_ACTIVE
	SteamAPI_Shutdown();
#endif
	return 0;
}