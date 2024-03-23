#pragma once
#include "GameObject.h"

namespace GameEngine {
	class ISubject;
	class IObserver
	{
	private:
		std::string m_Name{};
	public:
		virtual void Update(ISubject* subject) = 0;

		IObserver() = default;
		IObserver(const std::string& name);
		virtual ~IObserver() = default;
		IObserver(const IObserver& other) = delete;
		IObserver(IObserver&& other) = delete;
		IObserver& operator=(const IObserver& other) = delete;
		IObserver& operator=(IObserver&& other) = delete;
	};

	class HealthObserver : public IObserver, public GameObject
	{
	private:
		bool m_HasDied{ false };
	public:
		HealthObserver(const std::string& name);
		virtual void Update(ISubject* subject) override; // subject -> getState

	};
}

