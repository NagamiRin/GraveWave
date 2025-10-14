/**
 * PlayerStatus.h
 *
 * プレイヤーステータス
 */
#pragma once
#include "src/Actor/ActorStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			/**
			 * プレイヤーステータスクラス
			 */
			class PlayerStatus : public ActorStatus
			{
			private:
				/** 移動速度 */
				float m_moveSpeed = 0.0f;

			

			public:
				/** コンストラクタ */
				PlayerStatus();
				/** デストラクタ */
				~PlayerStatus();


				/** セットアップ */
				void Setup() override;


			public:
				float GetMoveSpeed() const { return m_moveSpeed; }
			};
		}
	}
}