/**
 * ZombieState.cpp
 *
 * ゾンビの各ステートの処理を行う
 */
#include "stdafx.h"
#include "ZombieState.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/ZombieStateMachine.h"
#include "src/Core/BattleManager.h"
#include "src/Core/ModelLOD.h"
#include "src/Effect/EffectManager.h"


namespace {
	constexpr float DEATH_ANIM_TIME = 4.0f;
	constexpr float HIT_ANIM_TIME = 2.0f;
	constexpr float DUSTCLOUD_FREQUENCY = 0.2f;
	constexpr float DUSTCLOUD_SCALE = 5.0f;
}


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			namespace
			{
				struct ZombieCallback : public btCollisionWorld::RayResultCallback
				{
					//ヒットフラグ
					bool isHit = false;
					btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace) override
					{
						// Enemyじゃない&&Gohstじゃない なら当たらない
						if (rayResult.m_collisionObject->getUserIndex() != nsApp::enCollision_Wall && rayResult.m_collisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT) {
							return rayResult.m_hitFraction;
						}
						isHit = true;
						return rayResult.m_hitFraction;
					}
				};
			}

			ZombieAttackState::ZombieAttackState(ZombieStateMachine* owner)
				: IState(owner)
			{
				//持ち主（ステートマシン）取得
				m_owner = GetOwner<ZombieStateMachine>();
			}


			ZombieAttackState::~ZombieAttackState()
			{
			}


			void ZombieAttackState::Enter()
			{
			}


			void ZombieAttackState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				float frequency = owner->GetStatus()->GetAttackFrequency();

				//一定時間ごとに攻撃
				m_currentTime += g_gameTime->GetFrameDeltaTime();
				if (m_currentTime >= frequency) {

					//攻撃可能に
					owner->SetAttack(true);

					//攻撃アニメーション再生
					owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Attack);

					//時間リセット
					m_currentTime = 0.0f;
				}

				//攻撃アニメーションが再生し終わっているなら待機アニメーション
				if (!owner->GetModel()->IsPlayAnimation()) {
					owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Idle);
				}
			}


			void ZombieAttackState::Exit()
			{
			}


			/**********************************************************/


			ZombieDeathState::ZombieDeathState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieDeathState::~ZombieDeathState()
			{
			}


			void ZombieDeathState::Enter()
			{
				//死亡アニメーション再生
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Death);
			}


			void ZombieDeathState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();

				//時間を数える
				m_currentTime += g_gameTime->GetFrameDeltaTime();

				//アニメーション再生から一定時間経ったらプールに戻す
				if (m_currentTime >= DEATH_ANIM_TIME) owner->SetRestore(true);
			}


			void ZombieDeathState::Exit()
			{
			}


			/**********************************************************/


			ZombieGetUpState::ZombieGetUpState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieGetUpState::~ZombieGetUpState()
			{
			}


			void ZombieGetUpState::Enter()
			{
				//起き上がりアニメーションを再生
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_GetUp);
			}


			void ZombieGetUpState::Update()
			{
			}


			void ZombieGetUpState::Exit()
			{
			}


			/**********************************************************/


			ZombieHitState::ZombieHitState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieHitState::~ZombieHitState()
			{
			}


			void ZombieHitState::Enter()
			{
				//被弾アニメーション再生
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Hit);
			}


			void ZombieHitState::Update()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();

				//時間数える
				m_currentTime += g_gameTime->GetFrameDeltaTime();

				//一定時間後に被弾状態を戻す
				if (m_currentTime >= HIT_ANIM_TIME) {
					owner->SetHit(false);
				}
			}


			void ZombieHitState::Exit()
			{
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();

				m_currentTime = 0.0f;
				owner->SetHit(false);
			}


			/**********************************************************/


			ZombieIdleState::ZombieIdleState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = owner;
			}


			ZombieIdleState::~ZombieIdleState()
			{
			}


			void ZombieIdleState::Enter()
			{
				//待機アニメーションを再生
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Idle);
			}


			void ZombieIdleState::Update()
			{
			}


			void ZombieIdleState::Exit()
			{
			}


			/**********************************************************/


			ZombieWalkState::ZombieWalkState(ZombieStateMachine* owner)
				: IState(owner)
			{
				m_owner = GetOwner<ZombieStateMachine>();
			}


			ZombieWalkState::~ZombieWalkState()
			{
			}


			void ZombieWalkState::Enter()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();

				//モデルの向き、移動方向を壁側に
				stateMachine->SetMoveDirection(Vector3::Back);
				stateMachine->SetDirection(Vector3::Back);

				//歩行アニメーションを再生
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				owner->GetModel()->PlayAnimation(Zombie::EnAnimationVar_Walk);
			}


			void ZombieWalkState::Update()
			{
				ZombieStateMachine* stateMachine = GetOwner<ZombieStateMachine>();
				auto* owner = GetOwner<ZombieStateMachine>()->GetOwner();
				auto* ownerStatus = owner->GetStatus();

				//1フレームの移動量を計算
				const Vector3 moveAmount = stateMachine->GetMoveDirection() * stateMachine->GetMoveSpeed();

				//位置をセット
				stateMachine->SetPosition(stateMachine->GetPosition() + moveAmount);

				//レイを飛ばして、壁に当たったら攻撃状態に移行させる
				{
					//レイの始点
					Vector3 startPos = owner->GetLocalPosition();

					//レイの終点
					//始点 + (移動方向 * 移動速度)
					Vector3 endPos = startPos + (owner->GetDirection() * ownerStatus->GetMoveSpeed());

					ZombieCallback cb;

					//壁に当たったか判定
					bool isHit = PhysicsWorld::GetInstance()->RayTest(startPos, endPos, cb, [](const btCollisionWorld::RayResultCallback* result)
						{
							const auto* resultCB = dynamic_cast<const ZombieCallback*>(result);
							if (resultCB->isHit) {
								return true;
							}
							return false;
						});

					// 壁にたどり着いたら攻撃させる
					if (isHit) {
						owner->SetAttackState(true);
					}

					//一定時間おきに土煙のエフェクトを再生
					m_elapsedTime += g_gameTime->GetFrameDeltaTime();
					if (m_elapsedTime >= DUSTCLOUD_FREQUENCY) {
						//EffectManager::Get().PlayEffect(enEffectKind_DustCloud, owner->GetPosition(), owner->GetLocalRotation(), Vector3::One * DUSTCLOUD_SCALE);

						m_elapsedTime = 0.0f;
					}				
				}
			}


			void ZombieWalkState::Exit()
			{
				//移動方向をリセット
				auto* stateMachine = GetOwner<ZombieStateMachine>();
				stateMachine->SetMoveDirection(Vector3::Zero);
			}			
		}
	}
}