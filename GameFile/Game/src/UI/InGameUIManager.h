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
		enNotifyType_Countdown,
		enNotifyType_RemainingBullets,
		enNotifyType_RemainingEnemies,
		enNotifyType_Score,
		enNotifyType_WallHP,
		enNotifyType_None,
	};


	struct INotify
	{
		EnNotifyType m_notifyType;
		//
		INotify(EnNotifyType type) : m_notifyType(type) {}
	};

	struct RemainingBulletsNotify : public INotify
	{
		uint8_t m_remainingNum;
		uint8_t m_maxNum;
		//
		RemainingBulletsNotify()
			: INotify(enNotifyType_RemainingBullets)
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


	namespace nsUI
	{
		class Crosshair;
		class RemainingBulletsUI;
		class ScoreUI;
		class RemainingEnemyUI;
		class WallHPUI;
		class CountdownUI;


		class InGameUIManager
		{
		private:
			/** クロスヘア */
			Crosshair* m_crosshair = nullptr;
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


