/**
 * GameFlowManager.h
 *
 * インゲームの流れを管理するクラス
 */
#pragma once


enum EnInGameFlow {
	enBattle = 0,
	enPreparation,
	enNum
};

namespace nsApp
{
	namespace nsFlow
	{
		/**
		 * インゲームの流れを管理するクラス
		 */
		class GameFlowManager
		{
			friend class BattleFlow;
			friend class PreparationFlow;


		private:
			/** 現在のフェーズ */
			EnInGameFlow m_currentPhase = EnInGameFlow::enNum;
			/** 現在のウェーブ数 */
			uint8_t m_waveCount = 0;
			/** フェーズを切り替えたか */
			bool m_isChangePhase = false;


		private:
			GameFlowManager();
			~GameFlowManager();


		public:
			/** 更新処理 */
			void Update();


		private:
			/** 次のフェーズに切り替える */
			void SwitchNextPhase();


		public:
			/** ゲームクリア条件を満たしたか */
			bool IsClearConditions() const;
			/** 現在のゲームフェーズを取得 */
			inline EnInGameFlow GetGameFlow() const { return m_currentPhase; }
			/** 現在のウェーブ数を取得 */
			inline const uint8_t GetWaveCount() { return m_waveCount; }


		private:
			/** 自身のインスタンス */
			static GameFlowManager* m_instance;


		public:
			/** GameFlowManagerクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new GameFlowManager();
				}
			}
			/** GameFlowManagerクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** BattleManagerクラスのインスタンスを取得 */
			static GameFlowManager* GetInstance() { return m_instance; }
		};
	}
}


