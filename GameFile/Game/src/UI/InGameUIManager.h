/**
 * InGameUIManager.h
 *
 * UIの基底クラス
 */
#pragma once


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class Zombie;
		}
		namespace nsGun
		{
			class HandGun;
		}
	}
}

namespace nsApp
{
	enum EnNotifyType
	{
		enNotifyType_CrossHair,
		enNotifyType_Countdown,
		enNotifyType_RemainingBullets,
		enNotifyType_Reloading,
		enNotifyType_RemainingEnemies,
		enNotifyType_Enemies,
		enNotifyType_Caveat,
		enNotifyType_Score,
		enNotifyType_Shop,
		enNotifyType_SwitchPhase,
		enNotifyType_WallHP,
		enNotifyType_None,
	};


	struct INotify
	{
		EnNotifyType m_notifyType;
		//
		INotify(EnNotifyType type) : m_notifyType(type) {}
	};

	struct CrossHairNotify : public INotify
	{
		bool m_isAiming;
		bool m_isHit;
		//
		CrossHairNotify()
			: INotify(enNotifyType_CrossHair)
		{
		}
	};

	struct RemainingBulletsNotify : public INotify
	{
		uint8_t m_remainingNum;
		uint8_t m_maxNum;
		std::string m_gunName;
		//
		RemainingBulletsNotify()
			: INotify(enNotifyType_RemainingBullets)
		{
		}
	};

	struct ReloadingNotify : public INotify
	{
		float m_reloadTime;
		float m_currentReloadTime;
		//
		ReloadingNotify()
			: INotify(enNotifyType_Reloading)
		{
		}
	};

	struct RemainingEnemiesNotify :public INotify
	{
		uint8_t m_remainingEnemy;
		//
		RemainingEnemiesNotify()
			: INotify(enNotifyType_RemainingEnemies)
		{
		}
	};

	struct EnemiesNotify :public INotify
	{
		uint64_t m_iconId;
		uint32_t m_id;
		Vector3 m_position;
		//
		EnemiesNotify()
			: INotify(enNotifyType_Enemies)
		{
		}
	};

	struct CaveatNotify :public INotify
	{
		uint64_t m_caveatId;
		uint32_t m_id;
		Vector3 m_position;
		//
		CaveatNotify()
			: INotify(enNotifyType_Caveat)
		{
		}
	};

	struct WallHPNotify :public INotify
	{
		uint16_t m_maxWallHP;
		uint16_t m_wallHP;
		//
		WallHPNotify()
			: INotify(enNotifyType_WallHP)
		{
		}
	};

	struct ScoreNotify : public INotify
	{
		uint16_t m_score;
		//
		ScoreNotify()
			: INotify(enNotifyType_Score)
		{
		}
	};

	struct ShopNotify : public INotify
	{
		uint16_t m_menuIndex;
		bool m_isOpen;
		//
		ShopNotify()
			: INotify(enNotifyType_Shop)
		{
		}
	};

	struct CountdownNotify :public INotify
	{
		float m_specifiedSeconds;
		float m_currentSeconds;
		bool m_isDrawCount;
		//
		CountdownNotify()
			:INotify(enNotifyType_Countdown)
		{
		}
	};

	struct PhaseSwitchNotify :public INotify
	{
		uint8_t m_currentPhase;
		uint8_t m_waveNum;
		//
		PhaseSwitchNotify()
			:INotify(enNotifyType_SwitchPhase)
		{
		}
	};

	
	namespace nsUI
	{
		class Crosshair;
		class RemainingBulletsUI;
		class ScoreUI;
		class RemainingEnemyUI;
		class WallHPUI;
		class CountdownUI;
		class MiniMapUI;
		class ShopUI;
		class CaveatUI;
		class PhaseSwitchUI;
		class ReloadingUI;


		class InGameUIManager
		{
		private:
			/** クロスヘア */
			Crosshair* m_crosshairUI = nullptr;
			/** カウントダウン */
			CountdownUI* m_countdownUI = nullptr;
			/** 残弾数 */
			RemainingBulletsUI* m_remainingBulletsUI = nullptr;
			/** スコア */
			ScoreUI* m_scoreUI = nullptr;
			/** エネミーの残数 */
			RemainingEnemyUI* m_remainingEnemyUI = nullptr;
			/** 防壁のHP */
			WallHPUI* m_wallHPUI = nullptr;
			/** ミニマップ */
			MiniMapUI* m_miniMapUI = nullptr;
			/** ショップUI */
			ShopUI* m_shopUI = nullptr;
			/** 警告UI */
			CaveatUI* m_caveatUI = nullptr;
			/** フェーズ切り替えのメッセージUI */
			PhaseSwitchUI* m_phaseSwitch = nullptr;
			/** リロード時間UI */
			ReloadingUI* m_reloadingUI = nullptr;


			std::vector<INotify*> m_notifyList;


		private:
			/** コンストラクタ */
			InGameUIManager();
			/** デストラクタ */
			~InGameUIManager();


		public:
			/** 更新処理 */
			void Update();


		public:
			void AddNotify(INotify* notify)
			{
				m_notifyList.push_back(notify);
			}


		private:
			/** 自身のインスタンス */
			static InGameUIManager* m_instance;


		public:
			/** InGameUIManagerのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new InGameUIManager();
				}
			}
			/** InGameUIManagerのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** InGameUIManagerのインスタンスを取得 */
			static InGameUIManager* GetInstance() { return m_instance; }
		};
	}
}


