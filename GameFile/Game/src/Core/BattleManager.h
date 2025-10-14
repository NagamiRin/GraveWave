/**
 * BattleManager.h
 *
 * 戦闘全体を管理するクラス
 */
#pragma once

/** 前方宣言 */
namespace nsApp
{
	class GameCamera;


	namespace nsActor
	{
		namespace nsPlayer
		{
			class Player;
		}
	}
}



namespace nsApp
{
	namespace nsCore
	{

		/**
		 *ゲームオブジェクトの基底クラス
		 */
		class BattleManager
		{
		private:
			/** カメラ位置をプレイヤーに合わせて更新 */
			void UpdateCameraForPlayer();
			/** 銃に発砲させるかを判断 */
			void JudgOnFire();


		private:
			/** カメラ */
			nsApp::GameCamera* m_camera = nullptr;
			/** プレイヤー */
			nsApp::nsActor::nsPlayer::Player* m_player = nullptr;


		private:
			/** コンストラクタ */
			BattleManager();
			/** デストラクタ */
			~BattleManager();


		public:
			/** 更新処理 */
			void Update();


		private:
			/** 自身のインスタンス */
			static BattleManager* m_instance;


		public:
			/** BattleManagerクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new BattleManager();
				}
			}
			/** BattleManagerクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** BattleManagerクラスのインスタンスを取得 */
			static BattleManager* GetInstance() { return m_instance; }
		};
	}
}


