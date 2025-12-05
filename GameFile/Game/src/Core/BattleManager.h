/**
 * BattleManager.h
 *
 * 戦闘全体を管理するクラス
 */
#pragma once



namespace nsApp
{
	namespace nsCamera
	{
		class GameCamera;
	}

	namespace nsUI
	{
		class InGameUIManager;
	}

	namespace nsActor
	{
		namespace nsBackGround
		{
			class BackGround;
		}

		namespace nsEnemy
		{
			class EnemySpawner;
			class Zombie;
		}

		namespace nsPlayer
		{
			class Player;
		}		

		namespace nsWall
		{
			class Wall;
		}
	}
}


namespace nsApp
{
	namespace nsBattle
	{
		enum EnNotifyType
		{
			enNotifyType_BuyGun,
			enNotifyType_BuyAmmo,
			enNotifyType_None,
		};


		struct INotify
		{
			EnNotifyType m_notifyType;
			//
			INotify(EnNotifyType type) : m_notifyType(type) {}
		};


		struct BuyGunNotify : public INotify
		{
			uint32_t m_gunType;
			uint32_t m_gunID;
			//
			BuyGunNotify()
				: INotify(enNotifyType_BuyGun)
			{
			}
		};		
	}
}


namespace nsApp
{
	namespace nsCore
	{
		/**
		 * インゲーム全体を管理するクラス
		 */
		class BattleManager
		{
			using EnemySpawnerPtr = std::unique_ptr<nsApp::nsActor::nsEnemy::EnemySpawner>;


		private:
			/** 背景 */
			nsActor::nsBackGround::BackGround* m_backGround = nullptr;
			/** 防壁 */
			nsActor::nsWall::Wall* m_wall = nullptr;
			/** カメラ */
			nsCamera::GameCamera* m_camera = nullptr;
			/** プレイヤー */
			nsActor::nsPlayer::Player* m_player = nullptr;
			/** エネミーのスポナー(右) */
			std::array<EnemySpawnerPtr, enSpwnerType_Num> m_enemySpawner;


		private:
			/** エネミーが進行を止める位置（Z座標） */
			float m_enemyStopPosition = 0.0f;

			/** 通知のリスト */
			std::vector<nsApp::nsBattle::INotify*> m_notifyList;



		private:
			/** カメラ位置をプレイヤーに合わせて更新 */
			void UpdateCameraForPlayer();
			/** 銃に発砲させるかを判断 */
			void JudgOnFire();		


		private:
			/** コンストラクタ */
			BattleManager();
			/** デストラクタ */
			~BattleManager();


		public:
			/** 更新処理 */
			void Update();
			/** 遅延更新処理 */
			void LateUpdate();


		public:
			/**	通知を追加 */
			void AddNotify(nsApp::nsBattle::INotify* notify)
			{
				m_notifyList.push_back(notify);
			}
			/** ゾンビの削除要請 */
			void DeleteZombie(nsApp::nsActor::nsEnemy::Zombie* zombie);
			/** 水平方向の限界値を取得 */
			float GetVerLimitAngle();
			/** 垂直方向の限界値を取得 */
			float GetHorLimitAngle();
			/** 重力量を取得 */
			float GetGravityAmount();
			/** エネミーが進行を止める距離を取得 */
			float GetEnemyStopPosition();
			/** 防壁にダメージを与える */
			void DealingDamage(const uint16_t damage);
			/** リザルトへ移行していいか */
			bool IsBattleFinish()const;
			/** ゲームで勝ったか */
			bool IsBattleWin()const;
			/** ゲームで負けたか */
			bool IsBattleLose()const;

			//todo for test
			/** サブ武器のIDリストを取得 */
			const std::vector<uint32_t>& GetSubWeaponIDList() const;
			/** メイン武器のIDリストを取得 */
			const std::vector<uint32_t>& GetMainWeaponIDList() const;
			/** サブ武器のIDを登録 */
			void SetSubWeaponID(const uint32_t gunID);
			/** メイン武器のIDを登録 */
			void SetMainWeaponID(const uint32_t gunID);
			/** プレイヤーに武器の変更をリクエスト */
			void RequestChangeWeapon(const uint32_t weaponID);			 


		public:
			/** スポナーを取得 */
			inline nsApp::nsActor::nsEnemy::EnemySpawner* GetEnemySpawner(EnSpwnerType type)
			{
				return m_enemySpawner.at(type).get();
			}


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


