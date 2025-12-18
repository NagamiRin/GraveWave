/**
 * Boss.cpp
 *
 * Bossクラス
 */
#include "stdafx.h"
#include "Boss.h"
#include "src/Actor/Enemy/Boss/ThrowStone.h"
#include "src/Actor/Enemy/Boss/BossStateMachine.h"
#include "src/Collision/CollisionManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            Boss::Boss()
            {
                //自身のステータスを生成
                m_status = new BossStatus();

                //自身のステートマシンを生成
                m_stateMachine = std::make_unique<BossStateMachine>();
                m_stateMachine->Setup(this, GetStatus());

                //岩を生成
                m_throwStone = NewGO<nsEnemy::ThrowStone>(enGameObjectPriority_Stone, "ThrowStone");
            }


            Boss::~Boss()
            {
                //ステータスを削除
                delete m_status;
                m_status = nullptr;

                //岩を削除
                DeleteGO(m_throwStone);
            }


            bool Boss::Start()
            {
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                // アニメーションの初期化
                {
                    auto* clip = &m_animationClipList[EnAnimationVar_Idle];
                    clip->Load("Assets/AnimData/Boss/Idle.tka");
                    clip->SetLoopFlag(true);

                    clip = &m_animationClipList[EnAnimationVar_Walk];
                    clip->Load("Assets/AnimData/Boss/Walk.tka");
                    clip->SetLoopFlag(true);

                    clip = &m_animationClipList[EnAnimationVar_Throw];
                    clip->Load("Assets/AnimData/Boss/Throw.tka");
                    clip->SetLoopFlag(false);

                    clip = &m_animationClipList[EnAnimationVar_Hit];
                    clip->Load("Assets/AnimData/Boss/Hit.tka");
                    clip->SetLoopFlag(false);

                    clip = &m_animationClipList[EnAnimationVar_Death];
                    clip->Load("Assets/AnimData/Boss/Death.tka");
                    clip->SetLoopFlag(false);
                }
                m_model.Init("Assets/ModelData/Zombie/Boss/Boss.tkm", m_animationClipList.data(), EnAnimationVar_Max);
                return true;
            }
            

            void Boss::Update()
            {
                m_transform.UpdateTransform();

                m_collisionPosition = m_transform.m_position + Vector3(0.0f, 100.0f, 0.0f);
                if (m_collisionObject) {
                    m_collisionObject->SetPosition(m_collisionPosition);
                    m_collisionObject->Update();
                }
				m_model.SetPosition(m_transform.m_position);
                m_model.SetRotation(m_transform.m_rotation);
                m_model.Update();

                m_stateMachine->Update();

                SuperClass::Update();
            }


            void Boss::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }


            void Boss::Initialize(const Vector3& initializePosition)
            {
                GetStatus()->ResetHP();
                SetLocalPosition(initializePosition);                

                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 20.0f, 100.0f);
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollision_Enemy);
            }


            void Boss::Destruction()
            {
                if (!CollisionHitManager::Get().CheckCollision(this)) return;
                CollisionHitManager::Get().DeleteCollisionObject(this);
                m_collisionObject = nullptr;
            }


            void Boss::ThrowStone(const Vector3& start, const Vector3& end)
            {
                m_throwStone->SetThrowingInfo(start, end);
            }
        }
    }
}