/**
 * Zombie.cpp
 *
 * ゾンビ（雑魚）クラス
 */
#include "stdafx.h"
#include "Zombie.h"
#include "src/Actor/Enemy/ZombieStateMachine.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ModelLOD.h"


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

                //自身のステートマシンを生成
                m_stateMachine = std::make_unique<ZombieStateMachine>();
                m_stateMachine->Setup(this, GetZombieStatus());
            }


            Zombie::~Zombie()
            {
                //ステータスを削除
                delete m_status;
                m_status = nullptr;

                //LOD削除
                delete m_modelLOD;
            }


            bool Zombie::Start()
            {
                m_model.SetScale(0.3f, 0.3f, 0.3f);
                m_transform.m_localScale = Vector3(0.3f, 0.3f, 0.3f);
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                //LODの初期設定
                m_modelLOD = new nsCore::ModelLOD();
                m_modelLOD->Initialize({ "Assets/ModelData/Zombie/Default/LOD1.tkm","Assets/ModelData/Zombie/Default/Default.tkm"
                    /*,
                   "Assets/ModelData/Zombie/Default/LOD2.dds",
                   "Assets/ModelData/Zombie/Default/LOD3.dds" */ },
                    500.0f,
                    2);

                // アニメーションの初期化
                {
                    // 歩き
                    {
                        auto& clip = m_animationClipList[EnAnimationVar_Walk];
                        clip.Load("Assets/AnimData/Zombie/Walk.tka");
                        clip.SetLoopFlag(true);
                    }
                }
                m_model.Init("Assets/ModelData/Zombie/Default/Default.tkm", m_animationClipList.data(), EnAnimationVar_Max);
                m_model.PlayAnimation(EnAnimationVar_Walk);                

                return true;
            }
            

            void Zombie::Update()
            {
                m_transform.UpdateTransform();

                m_collisionPosition = m_transform.m_position + Vector3(0.0f, 25.0f, 0.0f);
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollirionEnemy);

				m_model.SetPosition(m_transform.m_position);
                m_model.SetRotation(m_transform.m_rotation);
                m_model.Update();

                //LODのいろいろ更新
                m_modelLOD->SetPosition(m_transform.m_localPosition);
                m_modelLOD->SetRotation(m_transform.m_localRotation);
                m_modelLOD->SetScale(m_transform.m_localScale);
                m_modelLOD->Update();

                m_stateMachine->Update();

                SuperClass::Update();
            }


            void Zombie::Render(RenderContext& rc)
            {
                m_modelLOD->Render(rc);
            }


            void Zombie::Initialize(const Vector3& initializePosition)
            {
                GetZombieStatus()->ResetHP();
                SetLocalPosition(initializePosition);                

                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 10.0f, 30.0f);                
            }


            void Zombie::Destruction()
            {
                if (!CollisionHitManager::Get().CheckCollision(this)) return;
                CollisionHitManager::Get().DeleteCollisionObject(this);

                //LODをリセット
                m_modelLOD->ResetLOD();
            }
        }
    }
}