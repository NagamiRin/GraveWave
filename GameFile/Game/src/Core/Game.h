/**
 * Game.cpp
 *
 * ゲーム全体を管理するクラス
 */
#pragma once
#include "Level3DRender/LevelRender.h"

/** 前方宣言 */
namespace nsApp {
	namespace nsActor {
		namespace nsPlayer {
			class Player;
		}
		namespace nsEnemy {
			class Zombie;
		}
	}
	namespace nsCore {
		class BattleManager;
	}
}


namespace nsApp
{
	namespace nsCore
	{
		/**
		 * ゲーム全体を管理するクラス
		 */
		class Game : public IGameObject
		{
		private:
			/** ゲーム進行管理クラスのポインタ */
			BattleManager* m_battleManager = nullptr;


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