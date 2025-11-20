/**
 * SaveData.h
 *
 * ゲームの状況などプレイデータを保持する
 */
#pragma once


namespace nsApp
{
	namespace nsCore
	{
		class SaveData : Noncopyable
		{
		private:
			uint16_t m_score;
			EnResultType m_resultType = enResultType_None;

		private:
			SaveData() {}
			~SaveData() {}


			/** 値の設定などここに関数を追加していく */
		public:
			/** スコアを設定 */
			inline void SetScore(const uint16_t score) { m_score = score; }
			/** スコアを取得 */
			inline uint16_t GetScore()const { return m_score; }
			/** リザルトの分岐を設定 */
			inline void SetResultType(const EnResultType type) { m_resultType = type; }
			/** リザルトの分岐を取得 */
			inline EnResultType GetResultType() const { return m_resultType; }

			/**
			 * シングルトン関連
			 */
		private:
			static SaveData* m_instance;


		public:
			static void Create()
			{
				if (m_instance == nullptr)
				{
					m_instance = new SaveData();
				}
			}
			static SaveData& Get()
			{
				// ポインタじゃなくて参照でわたす
				// 悪さされないように
				return *m_instance;
			}
			static void Delete()
			{
				if (m_instance) {
					delete m_instance;
					m_instance = nullptr;
				}
			}
		};
	}
}


