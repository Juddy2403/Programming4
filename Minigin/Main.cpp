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
#include "RotationComponent.h"
#include "IMGUIComponent.h"

using namespace GameEngine;
void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto gameObject = std::make_unique<GameObject>("Background");
	gameObject->AddComponent<TextureComponent>("background.tga");
	scene.Add(std::move(gameObject));

	gameObject = std::make_unique<GameObject>("Logo");
	gameObject->SetPosition(216.f, 180.f);
	gameObject->AddComponent<TextureComponent>("logo.tga");
	scene.Add(std::move(gameObject));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	gameObject = std::make_unique<GameObject>("Title");
	gameObject->SetPosition(80.f, 20.f);
	gameObject->AddComponent<TextComponent>(font,"Programming 4 Assignment");
	gameObject->AddComponent<TextureComponent>();
	scene.Add(std::move(gameObject));

	gameObject = std::make_unique<GameObject>("FPSCounter");
	gameObject->SetPosition(20.f, 80.f);
	gameObject->AddComponent<FPSComponent>(gameObject->AddComponent<TextComponent>(font, "160 FPS"));
	gameObject->AddComponent<TextureComponent>();
	scene.Add(std::move(gameObject));

	auto gameObject2 = std::make_unique<GameObject>("CenterPoint");
	gameObject2->SetPosition(300.f, 300.f);

	gameObject = std::make_unique<GameObject>("Pacman");
	gameObject->SetPosition(250.f, 250.f); 
	gameObject->SetParent(gameObject2.get());
	gameObject->AddComponent<TextureComponent>("pacman.png");
	gameObject->AddComponent<RotationComponent>(5.f);
	scene.Add(std::move(gameObject2));

	gameObject2 = std::make_unique<GameObject>("PacmanFemale");
	gameObject2->SetPosition(200.f, 200.f);
	gameObject2->AddComponent<TextureComponent>("PacmanFemale.png");
	gameObject2->SetParent(gameObject.get());
	gameObject2->AddComponent<RotationComponent>(7.f,false);
	scene.Add(std::move(gameObject));

	scene.Add(std::move(gameObject2));

	gameObject = std::make_unique<GameObject>("IMGUI");
	gameObject->AddComponent<IMGUIComponent>();
	scene.Add(std::move(gameObject));

}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}