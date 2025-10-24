/**
 * ZombieStatus.h
 *
 * ゾンビのステータス
 */
#pragma once
#include "src/Actor/Enemy/EnemyStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/**
			 * ゾンビステータスクラス
			 */
			class ZombieStatus : public EnemyStatus
			{
			public:
				/** コンストラクタ */
				ZombieStatus();
				/** デストラクタ */
				~ZombieStatus();


			public:
				/** セットアップ */
				void Setup() override;
			};
		}
	}
}