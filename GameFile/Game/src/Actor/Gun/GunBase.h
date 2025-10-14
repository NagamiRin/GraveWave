/**
 * GunBase.h
 *
 * 銃の基底クラス
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			/**
			 * 銃の基底クラス
			 */
			class GunBase : public Actor
			{
			protected:
				/** 残りの発射クールタイム(秒) */
				float m_fireCoolTime = 0.0f;


			public:
				/** コンストラクタ */
				GunBase();
				/** デストラクタ */
				virtual ~GunBase();

				virtual bool Start()override { return true; }
				virtual void Update()override {}
				virtual void Render(RenderContext& rc)override {}


			public:
				/** 発射クールタイムを取得 */
				const float GetFireCoolTime() { return m_fireCoolTime; }
			};
		}
	}
}