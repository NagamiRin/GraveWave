/**
 * BulletBase.cpp
 *
 * 弾の基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Bullet/BulletBase.h"
#include "src/Collision/CollisionManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			BulletBase::BulletBase()
			{
			}


			BulletBase::~BulletBase()
			{
			}


			bool BulletBase::Start() 
			{
				return true;
			}


			void BulletBase::Update()
			{
				FlyingProcessing();
				AutoDelete();
			}


			void BulletBase::Render(RenderContext& rc)
			{

			}


			void BulletBase::FlyingProcessing()
			{
				if (!m_isFlying) {
					return;
				}

				const Vector3 moveAmount = m_flyDirection * m_bulletSpeed;
				SetPosition(GetPosition() + moveAmount);
			}


			void BulletBase::AutoDelete()
			{
				m_flyingTime += g_gameTime->GetFrameDeltaTime();

				if (m_flyingTime >= 3.0f) {
					DeleteGO(this);
				}
			}
		}
	}
}