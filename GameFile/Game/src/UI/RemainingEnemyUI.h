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
		class NumberUI;
		class ImageUI;


		/**
		 * 敵の残数を表示するクラス
		 */
		class RemainingEnemyUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** エネミーの残数 */
			NumberUI* m_enemyCount = nullptr;
			/** ウエーブ表示の数列 */
			NumberUI* m_wave = nullptr;
			/** UIの枠 */
			ImageUI* m_lightFrame = nullptr;
			/** フェーズごとのメッセージ文 */
			ImageUI* m_massage = nullptr;
			/** エネミーの残数 */
			uint8_t m_count = 0;
			/** 現在のフェーズの種類 */
			uint8_t m_currentPhase = 0;

		public:
			/** コンストラクタ */
			RemainingEnemyUI();
			/** デストラクタ */
			~RemainingEnemyUI();


		public:
			/** エネミーの残数を設定 */
			inline void SetEnemyCount(const uint8_t count) { m_count = count; }


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;
		};
	}
}


