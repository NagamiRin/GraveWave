/**
 * EnemyStatus.h
 *
 * アクターステータス
 */
#pragma once

#include "src/Actor/ActorStatus.h"

namespace nsApp
{
	namespace nsActor
	{
		/**
		 * アクターのステータスクラス
		 * NOTE: 中身は空だが、すべてのステータスクラスの基底となる
		 */
		class EnemyStatus : public ActorStatus
		{
		private:
			/** 体力 */
			uint32_t m_hp = 0;


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