/**
 * NormalBullet.cpp
 *
 * 通常弾クラス
 */
#include "stdafx.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Collision/CollisionManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			NormalBullet::NormalBullet()
			{
			}


			NormalBullet::~NormalBullet()
			{
				CollisionHitManager::Get().DeleteCollisionObject(this);
			}


			bool NormalBullet::Start() 
			{
				m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, GetPosition(), GetRotation(), 3.0f);

				return true;
			}


			void NormalBullet::Update()
			{
				FlyingProcessing();
				AutoDelete();

				m_collisionObject->SetPosition(GetPosition());
				m_collisionObject->Update();
			}


			void NormalBullet::Render(RenderContext& rc)
			{

			}


			void NormalBullet::FlyingProcessing()
			{
				if (!m_isFlying) {
					return;
				}

				const Vector3 moveAmount = m_flyDirection * m_initialVelocity;
				SetPosition(GetPosition() + moveAmount);
			}


			void NormalBullet::AutoDelete()
			{
				m_flyingTime += g_gameTime->GetFrameDeltaTime();

				if (m_flyingTime >= 3.0f) {
					DeleteGO(this);
				}
			}
		}
	}
}