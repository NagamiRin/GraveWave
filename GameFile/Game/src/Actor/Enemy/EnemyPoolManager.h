/**
 * EnemyPoolManager.h
 *
 * エネミーのプールを管理
 */
#pragma once



namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class Zombie;
			class Boss;


			/**
			 * エネミーのプールを管理するクラス
			 */
			class EnemyPoolManager
			{
			private:
				//エネミーの情報
				template <typename T>
				struct PoolInformation
				{
					//エネミーのポインタ
					T* m_enemy = nullptr;
					//使用可能か(現在フィールドに出ていないか)
					bool m_canUse = true;
				};


			private:
				/** エネミーの配列 */
				std::vector<PoolInformation<Zombie>> m_zombiePool;
				/** ボスのインスタンス */
				PoolInformation<Boss> m_boss;
				/** 現在出現しているエネミーのリスト */
				std::vector<Zombie*> m_usedEnemyList;
				

			private:
				EnemyPoolManager();
				~EnemyPoolManager();
				

			private:
				/** 使えるやつを探して返す */
				PoolInformation<Zombie>* FindInformation();
				/** プールマネージャー削除時の後始末 */
				void CleaningUp();


			public:
				/** 初期化 */
				void SetUp(uint16_t maxEnemyNum);

				/** 使える人渡す */
				Zombie* FindUse();

				/** いらなくなったゾンビを戻す */
				void Restore(Zombie* target);
				/** HPがなくなったボスを撤収 */
				void RestoreBoss();


			public:
				/** 現在出現しているエネミーのリストを取得 */
				inline const std::vector<Zombie*>& GetUsedEnemyList() { return m_usedEnemyList; }
				/** 今使えるやつを探す */
				void ForEachUsedEnemy(const std::function<void(Zombie*)>& func);
				/** ボスを取得 */
				inline Boss* GetBoss() { return m_boss.m_enemy; }
				

			private:
				/** 自身のインスタンス */
				static EnemyPoolManager* m_instance;


			public:
				/** EnemyPoolManagerクラスのインスタンスを作成 */
				static void CreateInstance()
				{
					if (m_instance == nullptr)
					{
						m_instance = new EnemyPoolManager();
					}
				}
				/** EnemyPoolManagerクラスのインスタンスを削除 */
				static void DeleteInstance()
				{
					if (m_instance != nullptr)
					{
						delete m_instance;
						m_instance = nullptr;
					}
				}
				/** EnemyPoolManagerクラスのインスタンスを取得 */
				static EnemyPoolManager* GetInstance() { return m_instance; }
			};
		}
	}
}


