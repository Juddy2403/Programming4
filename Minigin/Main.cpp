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
	auto& scene = GameEngine::SceneManager::GetInstance().CreateScene("Demo");

	auto gameObject = std::make_shared<GameEngine::GameObject>("Background");
	gameObject->AddComponent<TransformComponent>();
	gameObject->AddComponent<TextureComponent>();
	gameObject->GetComponent<TextureComponent>()->SetTexture("background.tga");
	scene.Add(gameObject);

	gameObject = std::make_shared<GameEngine::GameObject>("Logo");
	gameObject->AddComponent<TransformComponent>();
	gameObject->AddComponent<TextureComponent>();
	gameObject->GetComponent<TextureComponent>()->SetTexture("logo.tga");
	gameObject->GetComponent<TransformComponent>()->SetPosition(216, 180);
	scene.Add(gameObject);

	auto font = GameEngine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	gameObject = std::make_shared<GameEngine::GameObject>("Title");
	gameObject->AddComponent<TransformComponent>();
	gameObject->AddComponent<TextComponent>();
	gameObject->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");
	gameObject->GetComponent<TextComponent>()->SetFont(font);
	gameObject->GetComponent<TransformComponent>()->SetPosition(80, 20);
	scene.Add(gameObject);

	gameObject = std::make_shared<GameEngine::GameObject>("FPSCounter");
	gameObject->AddComponent<TransformComponent>();
	gameObject->AddComponent<FPSComponent>();
	gameObject->AddComponent<TextComponent>();
	gameObject->GetComponent<TextComponent>()->SetText("160 FPS");
	gameObject->GetComponent<TextComponent>()->SetFont(font);
	gameObject->GetComponent<TransformComponent>()->SetPosition(20, 80);
	scene.Add(gameObject);
}

int main(int, char*[]) {
	GameEngine::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}