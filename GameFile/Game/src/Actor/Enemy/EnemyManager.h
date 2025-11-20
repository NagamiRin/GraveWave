/**
 * EnemySpawner.h
 *
 * エネミーの管理を行うクラス
 */
#pragma once



namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class Zombie;


			/**
			 * エネミーの管理者
			 */
			class EnemyManager
			{
			public:
				/** コンストラクタ */
				EnemyManager();
				/** デストラクタ */
				~EnemyManager();
			

			private:
				/** 自身のインスタンス */
				static EnemyManager* m_instance;


			public:
				/** EnemyManagerクラスのインスタンスを作成 */
				static void CreateInstance()
				{
					if (m_instance == nullptr)
					{
						m_instance = new EnemyManager();
					}
				}
				/** EnemyManagerクラスのインスタンスを削除 */
				static void DeleteInstance()
				{
					if (m_instance != nullptr)
					{
						delete m_instance;
						m_instance = nullptr;
					}
				}
				/** EnemyManagerクラスのインスタンスを取得 */
				static EnemyManager* GetInstance() { return m_instance; }
			};
		}
	}
}


