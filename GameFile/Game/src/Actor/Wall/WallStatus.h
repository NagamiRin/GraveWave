/**
 * WallStatus.h
 *
 * 防壁のステータス
 */
#pragma once

#include "src/Actor/ActorStatus.h"

namespace nsApp
{
	namespace nsActor
	{
		namespace nsWall
		{
			/**
		     * 防壁のステータスクラス
		     */
			class WallStatus : public ActorStatus
			{
			private:
				/** 耐久度 */
				uint16_t m_durability = 0;


			public:
				/** コンストラクタ */
				WallStatus();
				/** デストラクタ */
				~WallStatus();


				/** セットアップ */
				void Setup() override;
			};
		}
	}
}