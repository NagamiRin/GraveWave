/**
 * EnemySpawner.h
 *
 * エネミーのスポナークラス
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
			 * エネミースポナー
			 */
			class EnemySpawner
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
				/** エネミーの基準生成間隔（時間） */
				float m_baseSpawnTime = 0.0f;
				/** エネミーを生成してからの時間 */
				float m_spawnCoolTime = 0.0f;
				/** リスポーン位置 */
				Vector3 m_spawnPosition = Vector3::Zero;


			public:
				/** コンストラクタ */
				EnemySpawner(uint8_t enemyNum, float baseSpawnPosition, Vector3 spawnPosition);
				/** デストラクタ */
				~EnemySpawner();


			public:
				/** ゾンビの生成(プールから取得してくる) */
				Zombie* Create();
				/** エネミーの削除 */
				void Delete(Zombie* target);


			public:
				/** エネミーの生成時間を数える */
				inline void CountTime() 
				{
					if (m_spawnCoolTime <= 0.0f) {
						m_spawnCoolTime = 0.0f;
						return;
					}
					m_spawnCoolTime -= g_gameTime->GetFrameDeltaTime(); 
				}
			};
		}
	}
}


