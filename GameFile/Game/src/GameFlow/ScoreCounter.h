/**
 * ScoreCounter.h
 *
 * スコアを計算するクラス
 */
#pragma once


namespace nsApp
{
	namespace nsFlow
	{
		/**
		 * スコアを計算するクラス
		 */
		class ScoreCounter
		{
		private:
			/** 現在の合計スコア */
			uint16_t m_score = 0;
			/** スコア加算の種類 */
			std::map< EnScoreType, uint16_t> m_scoreVar;


		private:
			ScoreCounter();
			~ScoreCounter();


		public:
			/** 更新処理 */
			void Update();


		public:
			/** スコアを取得 */
			inline uint16_t GetScore() { return m_score; }
			/** スコアを加算 */
			void AddScore(const EnScoreType type);


		private:
			/** 自身のインスタンス */
			static ScoreCounter* m_instance;


		public:
			/** ScoreCounterクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new ScoreCounter();
				}
			}
			/** ScoreCounterクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** ScoreCounterクラスのインスタンスを取得 */
			static ScoreCounter* GetInstance() { return m_instance; };
		};
	}
}
