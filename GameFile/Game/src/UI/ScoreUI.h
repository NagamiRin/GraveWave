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
		class NumberUI;


		/**
		 * スコアを計算、管理するクラス
		 */
		class ScoreUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 所持金の数列 */
			NumberUI* m_money = nullptr;

			/** 現在所持金 */
			uint16_t m_currentMoney = 0;

		public:
			/** コンストラクタ */
			ScoreUI();
			/** デストラクタ */
			~ScoreUI();


		public:
			/** スコアを設定 */
			inline void SetMoney(const uint16_t score) { m_currentMoney = score; }


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


