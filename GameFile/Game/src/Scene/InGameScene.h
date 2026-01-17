/**
 * InGameScene.h
 *
 * インゲームシーン
 */
#pragma once
#include "src/Scene/IScene.h"


namespace nsApp {
	namespace nsCore {
		class BattleManager;
	}
}

namespace nsApp
{
	namespace nsScene
	{
		/**
		 * インゲームシーン
		 */
		class InGameScene :public IScene
		{
		public:
			appScene(InGameScene);

			ModelRender test;

		public:
			InGameScene();
			~InGameScene();


		public:
			bool Start()override;
			void Update() override;
			bool RequestScene(uint32_t& id)override;
		};
	}
}


