/**
 * TitleScene.h
 *
 * タイトルシーン
 */
#pragma once
#include "src/Scene/IScene.h"


namespace nsApp {
	namespace nsUI {
		class TitleUIManager;
	}
}


namespace nsApp
{
	namespace nsScene
	{
		/**
		 * タイトルシーン
		 */
		class TitleScene :public IScene
		{
		public:
			appScene(TitleScene);


		public:
			/** コンストラクタ */
			TitleScene();
			/** デストラクタ */
			~TitleScene();

		public:
			bool Start()override;
			void Update()override;
			bool RequestScene(uint32_t& id)override;
		};
	}
}


