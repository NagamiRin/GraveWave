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


			void HandGun::OnFire()
			{
				nsApp::nsActor::nsBullet::NormalBullet* m_bullet = nullptr;
				// 弾を生成
				m_bullet = NewGO<nsApp::nsActor::nsBullet::NormalBullet>(enGameObjectPriority_Bullet, "NormalBullet");
				// 弾に初期値や初速を渡す
				m_bullet->SetPosition(GetPosition());
				m_bullet->SetInitialVelocity(10.0f);
				// 弾側で初速等をもとに移動させる
				m_bullet->SetFlying(true);

				// @todo for test
				// とりあえず前に出してみる
				m_bullet->SetDirection(Vector3::Front);
			}
		}
	}
}