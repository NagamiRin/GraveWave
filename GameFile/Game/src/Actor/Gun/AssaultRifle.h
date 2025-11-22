/**
 * AssaultRifle.h
 *
 * アサルトライフルクラス
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
			 * アサルトライフルクラス
			 */
			class AssaultRifle : public GunBase
			{
				appGameObject(AssaultRifle);

			public:
				/** コンストラクタ */
				AssaultRifle();
				/** デストラクタ */
				~AssaultRifle();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;
			};
		}
	}
}