#pragma once
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

#include "SteamAchievements.h"
#include "Singleton.h"
#include <memory>

namespace GameEngine {
	class CSteamAchievements;
	enum EAchievements
	{
		ACH_WIN_ONE_GAME = 0,
		ACH_WIN_100_GAMES = 1,
		ACH_TRAVEL_FAR_ACCUM = 2,
		ACH_TRAVEL_FAR_SINGLE = 3,
	};

	class AchievementsManager final : public Singleton<AchievementsManager>
	{
	private:
		Achievement_t m_Achievements[4] =
		{
			_ACH_ID(ACH_WIN_ONE_GAME, "Winner"),
			_ACH_ID(ACH_WIN_100_GAMES, "Champion"),
			_ACH_ID(ACH_TRAVEL_FAR_ACCUM, "Interstellar"),
			_ACH_ID(ACH_TRAVEL_FAR_SINGLE, "Orbiter"),
		};

		std::unique_ptr<CSteamAchievements> m_SteamAchievements;
	public:
		void SetAchievement(const char* ID);

		friend class Singleton<AchievementsManager>;
		void Init();
		AchievementsManager() = default;
	};
}


