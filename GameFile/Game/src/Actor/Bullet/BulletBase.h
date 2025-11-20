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
				using SuperClass = BulletBase;

				/** 弾のダメージ */
				uint8_t m_damage = 0;
				/** 弾の初速 */
				float m_bulletSpeed = 0.0f;
				/** 現在の飛翔時間 */
				float m_flyingTime = 0.0f;
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


			private:
				/** 飛翔中処理 */
				void FlyingProcessing();
				/** 自動削除 */
				void AutoDelete();


			public:
				inline void SetFlyDirection(const Vector3& direction) { m_flyDirection = direction; }
				/** パラメーターを設定 */
				inline void SetParameter(const float speed, const uint8_t damage) {
					m_bulletSpeed = speed;
					m_damage = damage;
				}
				/** 飛翔中フラグを設定 */
				inline void SetFlying(const float isFlying) { m_isFlying = isFlying; }
				/** 飛翔中フラグを取得 */
				inline bool IsFlying() const { return m_isFlying; }
			};
		}
	}
}