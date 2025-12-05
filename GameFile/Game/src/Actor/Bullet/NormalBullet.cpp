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
			namespace {
				struct BulletCallback : public btCollisionWorld::ConvexResultCallback
				{
					bool isHit = false;
					CollisionObject* m_me;
					//btCollisionObject* m_me = nullptr;
					const btCollisionObject* m_you = nullptr;

					btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) override
					{
						//自分自身を弾く
						if (&m_me->GetbtCollisionObject() == convexResult.m_hitCollisionObject) return 0.0f;
						
						//エネミー以外かつゴーストオブジェクトではない時
						if (convexResult.m_hitCollisionObject->getUserIndex() != nsApp::enCollirionEnemy 
							&& convexResult.m_hitCollisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT) {
							return 0.0f;
						}

						isHit = true;
						m_you = convexResult.m_hitCollisionObject;
						
						return 0.0f;
					}
				};
			}


			NormalBullet::NormalBullet()
			{
			}


			NormalBullet::~NormalBullet()
			{
				if (CollisionHitManager::Get().IsAvailable()) {
					if (!CollisionHitManager::Get().CheckCollision(this)) return;
					CollisionHitManager::Get().DeleteCollisionObject(this);
				}
			}


			bool NormalBullet::Start() 
			{
				//コリジョンマネージャーが消えているならreturn
				if (!&CollisionHitManager::Get()) {
					return true;
				}

				m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, GetPosition(), GetRotation(), 3.0f);

				return true;
			}


			void NormalBullet::Update()
			{
				SuperClass::Update();

				m_collisionObject->SetPosition(m_transform.m_localPosition);
				m_collisionObject->Update();

				SphereCollider collider;
				collider.Create(50.0f);
				Vector3 start = m_transform.m_position;
				Vector3 end = m_flyDirection * m_bulletSpeed;
				BulletCallback cb;
				//todo for test
				//meの登録
				//cb.m_me =
				PhysicsWorld::GetInstance()->ConvexSweepTest(collider, start, end, cb);
				if (cb.isHit) {
					for (CollisionInfo col : CollisionHitManager::Get().GetCollisionInfoList()) {
						if (&col.m_collision->GetbtCollisionObject() == cb.m_you) {
							col.m_target = cb.m_you;
							col.m_isHit = true;
						}
					}
				}
			}


			void NormalBullet::Render(RenderContext& rc)
			{

			}
		}
	}
}