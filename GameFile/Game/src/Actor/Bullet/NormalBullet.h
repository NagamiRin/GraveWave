/**
 * NormalBullet.h
 *
 * 通常弾クラス
 */
#pragma once
#include "src/Actor/ActorStatus.h"
#include "src/Actor/Bullet/Bulletbase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			/**
			 * 通常弾クラス
			 */
			class NormalBullet : public BulletBase
			{
				appGameObject(NormalBullet);


			private:
				/** 飛翔中処理 */
				void FlyingProcessing();
				/** 自動削除 */
				void AutoDelete();


			private:
				/** 現在の飛翔時間 */
				float m_flyingTime = 0.0f;


			public:
				/** コンストラクタ */
				NormalBullet();
				/** デストラクタ */
				~NormalBullet();


			public:
				bool Start()override;
				void Update()override;
				void Render(RenderContext& rc)override;
			};
		}
	}
}