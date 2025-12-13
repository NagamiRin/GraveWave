/**
 * TitleScene.h
 *
 * タイトルシーン
 */
#pragma once
#include "src/Scene/IScene.h"


namespace nsApp
{
	namespace nsScene
	{
		/**
		 * タイトルシーン
		 */
		class DebugScene :public IScene
		{
		public:
			appScene(DebugScene);


		public:
			/** コンストラクタ */
			DebugScene();
			/** デストラクタ */
			~DebugScene();

		public:
			bool Start()override;
			void Update()override;
			bool RequestScene(uint32_t& id)override;
		};
	}
}


