/**
 * GunStatus.h
 *
 * 銃のステータス
 */
#pragma once
#include "src/Actor/ActorStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			/**
			 * 銃のステータスクラス
			 */
			class GunStatus : public ActorStatus
			{
			private:
				/** ダメージ量 */
				uint8_t m_damage = 0;
				/** 最大弾数 */
				uint8_t m_maxBullet = 0;
				/** 弾速 */
				float m_bulletSpeed = 0.0f;

			public:
				/** コンストラクタ */
				GunStatus();
				/** デストラクタ */
				~GunStatus();


				/** セットアップ */
				void Setup() override;
			};
		}
	}
}