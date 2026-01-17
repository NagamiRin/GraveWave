/**
 * SubWeapon.h
 *
 * サブ武器クラス
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
			 * サブ武器クラス
			 */
			class SubWeapon : public GunBase
			{
				appGameObject(SubWeapon);


			public:
				SubWeapon();
				~SubWeapon();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;


			private:
				/** リロード完了 */
				void ReloadCompletion()override;
			};
		}
	}
}