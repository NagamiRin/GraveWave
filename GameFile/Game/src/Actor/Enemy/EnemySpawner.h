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
			/**
			 * エネミースポナー
			 */
			class EnemySpawner
			{
			private:
				/** リスポーン位置(Z値) */
				float m_spawnPositionZ = 0.0f;
				/** リスポーン位置（X値の最大値） */
				float m_maxXPosition = 0.0f;
				/** リスポーン位置（X値の最小値） */
				float m_minXPosition = 0.0f;
				/** ベースのリスポーン位置 */
				Vector3 m_baseSpawnPosition = Vector3::Zero;


			public:
				EnemySpawner(EnSpwnerType type);
				~EnemySpawner();


			public:
				/** ゾンビの生成(プールから取得してくる) */
				void ZombieCreate();
				/** ボスの生成 */
				void BossCreate();


			private:
				/** 敵のリスポーン位置を決める */
				Vector3 DecideSpawnPosition();
			};
		}
	}
}


