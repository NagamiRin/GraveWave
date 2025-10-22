/**
 * HandGun.cpp
 *
 * ハンドガンクラス
 */
#include "stdafx.h"
#include "src/Actor/Gun/HandGun.h"
#include "src/Actor/Bullet/NormalBullet.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			HandGun::HandGun()
			{
			}


			HandGun::~HandGun()
			{
			}


			bool HandGun::Start()
			{
				return true;
			}


			void HandGun::Update()
			{
				m_fireCoolTime -= g_gameTime->GetFrameDeltaTime();
				if (m_fireCoolTime <= 0.0f) {
					m_fireCoolTime = 0.0f;
				}
			}


			void HandGun::OnFire()
			{
				if (m_fireCoolTime > 0.0f) {
					return;
				}

				nsApp::nsActor::nsBullet::NormalBullet* m_bullet = nullptr;
				// 弾を生成
				m_bullet = NewGO<nsApp::nsActor::nsBullet::NormalBullet>(enGameObjectPriority_Bullet, "NormalBullet");
				// 弾に初期値や初速を渡す
				m_bullet->SetPosition(GetPosition());
				m_bullet->SetInitialVelocity(10.0f);
				// 弾側で初速等をもとに移動させる
				m_bullet->SetFlying(true);

				m_bullet->SetDirection(m_InjectionDirection);

				//クールタイムをセット
				m_fireCoolTime = 0.3f;
			}


			void HandGun::Render(RenderContext& rc)
			{

			}
		}
	}
}