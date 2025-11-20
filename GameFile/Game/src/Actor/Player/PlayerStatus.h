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
				/** 移動速度を取得 */
				inline float GetMoveSpeed() { return m_moveSpeed; }
			};
		}
	}
}