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
            }


            Zombie::~Zombie()
            {
            }


            bool Zombie::Start()
            {
                m_model.SetScale(0.3f, 0.3f, 0.3f);

                // アニメーションの初期化
                {
                    // 歩き
                    {
                        auto& clip = m_animationClipList[EnAnimationVar_Walk];
                        clip.Load("Assets/animData/Zombei/Walk.tka");
                        clip.SetLoopFlag(true);
                    }
                }
                m_model.Init("Assets/modelData/Zombie/Default.tkm", m_animationClipList.data(), EnAnimationVar_Max, enModelUpAxisY);
                m_model.PlayAnimation(EnAnimationVar_Walk);

                // @todo for test
                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, GetPosition(), GetRotation(), 10.0f, 50.0f);

                return true;
            }


            void Zombie::Update()
            {
                m_transform.UpdateTransform();
				m_model.SetPosition(m_transform.m_position);
                m_model.Update();
            }


            void Zombie::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }
        }
    }
}