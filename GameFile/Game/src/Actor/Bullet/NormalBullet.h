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
				void FlyingProcessing();


			public:
				/** コンストラクタ */
				NormalBullet();
				/** デストラクタ */
				~NormalBullet();


			public:
				bool Start()override;
				void Update()override;
				void Render(RenderContext& rc)override;


			public:
			};
		}
	}
}