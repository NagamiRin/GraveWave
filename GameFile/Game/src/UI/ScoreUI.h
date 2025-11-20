/**
 * ScoreUI.h
 *
 * スコアを計算、管理するクラス
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class StringUI;


		/**
		 * スコアを計算、管理するクラス
		 */
		class ScoreUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 文字UI */
			StringUI* m_scoreUI = nullptr;

			/** 現在の合計スコア */
			uint16_t m_score = 0;

		public:
			/** コンストラクタ */
			ScoreUI();
			/** デストラクタ */
			~ScoreUI();


		public:
			/** スコアを設定 */
			inline void SetScore(const uint16_t score) { m_score = score; }


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;


		public:
			/** ゾンビ討伐時のスコア加算 */
			inline void AddScoreZombieKill() {};
		};
	}
}


