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
				m_currentFlyTime += g_gameTime->GetFrameDeltaTime();
				if (m_currentFlyTime <= 0.0f) m_currentFlyTime = 0.0f;

				const Vector3 moveAmount = m_flyDirection * m_bulletSpeed;
				m_transform.m_localPosition = m_transform.m_localPosition + moveAmount;
			}


			void BulletBase::Render(RenderContext& rc)
			{

			}			
		}
	}
}