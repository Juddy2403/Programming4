#pragma once

//including vld
#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <SDL.h>
#include "Minigin.h"
#include <iostream>
#include "Galaga.h"

using namespace GameEngine;

void Load()
{
	Galaga::GetInstance().LoadLevel();
}

int main(int, char*[]) {
	
	Minigin engine("../Data/");
	engine.Run(Load);
	
    return 0;
}