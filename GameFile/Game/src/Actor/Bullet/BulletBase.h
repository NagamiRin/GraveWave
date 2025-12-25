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
				using SuperClass = Actor;


			protected:
				/** 弾のダメージ */
				uint8_t m_damage = 0;
				/** 弾の初速 */
				float m_bulletSpeed = 0.0f;
				/** 現在の飛翔時間 */
				float m_currentFlyTime = 0.0f;
				/** 弾の飛翔方向 */
				Vector3 m_flyDirection = Vector3::Zero;
				/** 自身のコリジョン */
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
				/** パラメーターを設定 */
				inline void SetParameter(const Vector3& position, const Vector3& direction,const float speed, const uint8_t damage) {
					m_transform.m_localPosition = position;
					m_flyDirection = direction;
					m_bulletSpeed = speed;
					m_damage = damage;
				}
				/** 現在の飛翔時間を取得 */
				inline float GetCurrentFlyTime()const { return m_currentFlyTime; };
				/** 弾の飛翔方向を取得 */
				inline const Vector3& GetFlyDirection() const { return m_flyDirection; }
				/** 弾の飛翔速度を取得 */
				inline const float GetBulletSpeed() const { return m_bulletSpeed; }
				/** 弾のダメージ量を取得 */
				inline const uint8_t GetDamage() { return m_damage; }
			};
		}
	}
}