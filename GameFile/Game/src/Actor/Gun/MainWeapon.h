/**
 * MainWeapon.h
 *
 * メイン武器クラス
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
			 * メイン武器クラス
			 */
			class MainWeapon : public GunBase
			{
				appGameObject(MainWeapon);

			public:
				MainWeapon();
				~MainWeapon();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;
			};
		}
	}
}