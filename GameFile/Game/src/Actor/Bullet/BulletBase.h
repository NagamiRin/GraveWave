/**
 * BulletBase.h
 *
 * 通常弾クラス
 */
#pragma once
#include "src/Actor/ActorStatus.h"
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			/**
			 * 通常弾クラス
			 */
			class BulletBase : public Actor
			{
			protected:
				/** 弾の初速 */
				float m_initialVelocity = 0.0f;
				/** 弾の飛翔方向 */
				Vector3 m_flyDirection = Vector3::Zero;
				/** 弾が飛翔中かのフラグ */
				bool m_isFlying = false;

				CollisionObject* m_collisionObject = nullptr;


			public:
				/** コンストラクタ */
				BulletBase();
				/** デストラクタ */
				virtual ~BulletBase();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;


			public:
				void SetDirection(const Vector3& direction) { m_flyDirection = direction; }
				/** 初速を設定 */
				void SetInitialVelocity(const float Velocity) { m_initialVelocity = Velocity; }
				/** 飛翔中フラグを設定 */
				void SetFlying(const float isFlying) { m_isFlying = isFlying; }
				/** 飛翔中フラグを取得 */
				bool IsFlying() const { return m_isFlying; }
			};
		}
	}
}