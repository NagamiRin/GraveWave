/**
 * HandGun.h
 *
 * ハンドガンクラス
 */
#pragma once
#include "src/Actor/Gun/GunBase.h"

namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			class NormalBullet;
		}
	}
}


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			/**
			 * 銃のステータスクラス
			 */
			class HandGun : public GunBase
			{
			public:
				/** コンストラクタ */
				HandGun();
				/** デストラクタ */
				~HandGun();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;
			};
		}
	}
}