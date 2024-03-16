#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"

using namespace GameEngine;
void load()
{
	SceneManager::GetInstance().CreateScene("Demo");
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}