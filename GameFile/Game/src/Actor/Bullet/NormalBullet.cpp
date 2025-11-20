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
				if (!CollisionHitManager::Get().CheckCollision(this)) return;
				CollisionHitManager::Get().DeleteCollisionObject(this);
			}


			bool NormalBullet::Start() 
			{
				m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, GetPosition(), GetRotation(), 3.0f);

				return true;
			}


			void NormalBullet::Update()
			{
				SuperClass::Update();

				m_collisionObject->SetPosition(GetPosition());
				m_collisionObject->Update();
			}


			void NormalBullet::Render(RenderContext& rc)
			{

			}
		}
	}
}