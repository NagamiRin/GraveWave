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
				/** リスポーン位置(Z値) */
				float m_spawnPositionZ = 0.0f;
				/** リスポーン位置（X値の最大値） */
				float m_maxPos = 0.0f;
				/** リスポーン位置（X値の最小値） */
				float m_minPos = 0.0f;
				/** リスポーン位置 */
				Vector3 m_spawnPosition = Vector3::Zero;


			private:
				/** 敵のリスポーン位置を決める */
				Vector3 DecideSpawnPosition();

			public:
				EnemySpawner(EnSpwnerType type);
				~EnemySpawner();


			public:
				/** ゾンビの生成(プールから取得してくる) */
				Zombie* Create();			
			};
		}
	}
}


