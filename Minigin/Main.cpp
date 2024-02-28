#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include <iostream>

using namespace GameEngine;
void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto gameObject = std::make_shared<GameObject>("Background");
	gameObject->AddComponent<TextureComponent>(gameObject->AddComponent<TransformComponent>().get(), "background.tga");
	scene.Add(gameObject);

	gameObject = std::make_shared<GameObject>("Logo");
	gameObject->AddComponent<TextureComponent>(gameObject->AddComponent<TransformComponent>(216.f, 180.f).get(), "logo.tga");
	scene.Add(gameObject);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	gameObject = std::make_shared<GameObject>("Title");
	gameObject->AddComponent<TextComponent>("Programming 4 Assignment",font);
	gameObject->AddComponent<TextureComponent>(gameObject->AddComponent<TransformComponent>(80.f, 20.f).get());
	scene.Add(gameObject);

	gameObject = std::make_shared<GameObject>("FPSCounter");
	gameObject->AddComponent<FPSComponent>(gameObject->AddComponent<TextComponent>("160 FPS", font).get());
	gameObject->AddComponent<TextureComponent>(gameObject->AddComponent<TransformComponent>(20.f, 80.f).get());
	scene.Add(gameObject);
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}