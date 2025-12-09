/**
 * BossStatus.h
 *
 * ボスのステータス
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
			 * ボスステータスクラス
			 */
			class BossStatus : public EnemyStatus
			{
			public:
				/** コンストラクタ */
				BossStatus();
				/** デストラクタ */
				~BossStatus();
			};
		}
	}
}