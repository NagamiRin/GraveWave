/**
 * Game.cpp
 *
 * ゲーム全体を管理するクラス
 */
#pragma once
#include "Level3DRender/LevelRender.h"


namespace nsApp
{
	namespace nsCore
	{
		/**
		 * ゲーム全体を管理するクラス
		 */
		class Game : public IGameObject
		{
		public:
			/** コンストラクタ */
			Game();
			/** デストラクタ */
			~Game();


		public:
			/** 生成時に一度だけ実行 */
			bool Start();
			/** 更新処理 */
			void Update();
			/** 描画処理 */
			void Render(RenderContext& rc);
		};
	}	
}