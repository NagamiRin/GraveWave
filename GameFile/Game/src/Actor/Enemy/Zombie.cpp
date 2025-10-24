/**
 * Zombie.cpp
 *
 * ゾンビ（雑魚）クラス
 */
#include "stdafx.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Collision/CollisionManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            Zombie::Zombie()
            {
                //自身のステータスを生成
                m_status = new ZombieStatus();
                m_status->Setup();
            }


            Zombie::~Zombie()
            {
                //ステータスを削除
                delete m_status;
                m_status = nullptr;

                CollisionHitManager::Get().DeleteCollisionObject(this);
            }


            bool Zombie::Start()
            {
                m_model.SetScale(0.3f, 0.3f, 0.3f);
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                // アニメーションの初期化
                {
                    // 歩き
                    {
                        auto& clip = m_animationClipList[EnAnimationVar_Walk];
                        clip.Load("Assets/AnimData/Zombie/Walk.tka");
                        clip.SetLoopFlag(true);
                    }
                }
                m_model.Init("Assets/ModelData/Zombie/Default.tkm", m_animationClipList.data(), EnAnimationVar_Max);
                m_model.PlayAnimation(EnAnimationVar_Walk);

                return true;
            }
            

            void Zombie::Update()
            {
                //todo for test
                SetLocalPosition(GetLocalPosition() + Vector3(0.0f, 0.0f, -2.0f));

                m_transform.UpdateTransform();

                m_collisionPosition = m_transform.m_position + Vector3(0.0f, 25.0f, 0.0f);
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();

				m_model.SetPosition(m_transform.m_position);
                m_model.SetRotation(m_transform.m_rotation);
                m_model.Update();

                Vector3 hoge = GetDirection();
            }


            void Zombie::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }


            void Zombie::Initialize(const Vector3& initializePosition)
            {
                GetZombieStatus()->ResetHP();
                SetLocalPosition(initializePosition);
                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 10.0f, 30.0f);
            }


            void Zombie::Destruction()
            {
                //コリジョンの登録を解除する
                CollisionHitManager::Get().DeleteCollisionObject(this);
            }
        }
    }
}