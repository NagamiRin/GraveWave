/**
 * RemainingEnemyUI.h
 *
 * 敵の残数を表示するクラス
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class StringUI;


		/**
		 * 敵の残数を表示するクラス
		 */
		class RemainingEnemyUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 文字UI */
			StringUI* m_enemyCountUI = nullptr;

			/** エネミーの残数 */
			uint8_t m_enemyCount = 0;

		public:
			/** コンストラクタ */
			RemainingEnemyUI();
			/** デストラクタ */
			~RemainingEnemyUI();


		public:
			/** エネミーの残数を設定 */
			inline void SetEnemyCount(const uint8_t count) { m_enemyCount = count; }


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;
		};
	}
}


