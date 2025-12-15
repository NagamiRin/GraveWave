/**
 * BattleFlow.h
 *
 * 戦闘フェーズの処理
 */
#pragma once


enum EnWaveType {
	enWaveType_Normal,
	enWaveType_Boss,
	enWaveType_None,
};


namespace nsApp
{
	namespace nsFlow
	{
		/**
		 * 戦闘フェーズの処理
		 */
		class BattleFlow
		{
		private:
			/** スポナーのリスト */
			std::array<uint16_t, enSpwnerType_Num> m_spawnCountList;
			/** ウェーブで出現するエネミーの総数 */
			uint8_t m_waveEnemyNum = 0;
			/** 出現させる残りのエネミーの数 */
			uint8_t m_remainingEnemiesNum = 0;
			/** 出現させるボスの数 */
			bool m_isBossSpawn = 0;
			/** 倒したエネミーの数 */
			uint8_t m_eliminateEnemyNum = 0;
			/** エネミーの生成間隔 */
			float m_spawnInterval = 0.0f;
			/** 現在の生成してからの経過時間 */
			float m_currentTime = 0.0f;
			/** ボスを出現させたか */
			bool m_isSpawnBoss = false;
			/** ウェーブのタイプ */
			EnWaveType m_waveType = enWaveType_None;


		private:
			BattleFlow();
			~BattleFlow();


		public:
			/** 更新処理 */
			void Update();
			/** 各ウェーブの情報をセット */
			void SetInformation(uint8_t waveCount);


		private:
			/** エネミーを出現させる */
			void EnemySpawn();
			/** 次のフェーズに移行させる */
			void ChangeNextPhase();


		public:
			/** 倒した敵の数を加算する */
			inline void AddEliminateEnemy() { m_eliminateEnemyNum++; }
			/** エネミーの残数を取得 */
			inline uint8_t GetRemainingEnemy() { return m_waveEnemyNum - m_eliminateEnemyNum; }


		private:
			/** 自身のインスタンス */
			static BattleFlow* m_instance;


		public:
			/** BattleFlowクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new BattleFlow();
				}
			}
			/** BattleFlowクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** BattleFlowクラスのインスタンスを取得 */
			static BattleFlow* GetInstance() { return m_instance; }
		};
	}
}


