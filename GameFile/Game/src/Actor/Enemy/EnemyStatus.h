/**
 * EnemyStatus.h
 *
 * エネミーステータス
 */
#pragma once

#include "src/Actor/ActorStatus.h"

namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/**
			 * エネミーのステータスクラス
			 */
			class EnemyStatus : public ActorStatus
			{
			private:
				/** 体力 */
				uint16_t m_hp = 0;


			public:
				/** コンストラクタ */
				EnemyStatus();
				/** デストラクタ */
				~EnemyStatus();


				/** セットアップ */
				void Setup() override;
			};
		}
	}
}