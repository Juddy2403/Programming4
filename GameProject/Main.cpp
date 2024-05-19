//including vld
#ifdef _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Galaga.h"

void Load()
{
	Galaga::LoadLevel();
}

int main(int, char* []) {
	GameEngine::Minigin engine("../Data/");
	engine.Run(Load);

	return 0;
}