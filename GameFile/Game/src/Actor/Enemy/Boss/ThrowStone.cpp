/**
 * ThrowStone.cpp
 *
 * ボスが投げる岩クラス
 */
#include "stdafx.h"
#include "ThrowStone.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            ThrowStone::ThrowStone()
            {
                ParameterManager::Get().LoadParameter<MasterStoneParameter>("Assets/Parameter/StoneParameter.json", [](const nlohmann::json& j, MasterStoneParameter& p)
                    {
                        p.m_altitude = j["Altitude"].get<float>();
                        p.m_landingTime = j["LandingTime"].get<float>();
                        p.m_maxDurability = j["MaxDurability"].get<float>();
                        p.m_rotSpeed = j["RotSpeed"].get<float>();
                    });

                auto* param = ParameterManager::Get().GetParameter<MasterStoneParameter>();

                m_altitude = param->m_altitude;
                m_landingTime = param->m_landingTime;
                m_rotSpeed = param->m_rotSpeed;
                m_maxDurability = param->m_maxDurability;
            }


            ThrowStone::~ThrowStone()
            {

            }


            bool ThrowStone::Start()
            {
                SetDirection(Vector3(0.0f, 0.0f, -1.0f));

                m_model.Init("Assets/ModelData/Zombie/Boss/Stone.tkm");

                return true;
            }
            

            void ThrowStone::Update()
            {
                //飛翔中でないなら処理しない
                if (!m_isFlying) return;
                if (m_elapsedTime >= m_landingTime) {
                    if (!CollisionHitManager::Get().CheckCollision(this)) return;
                    CollisionHitManager::Get().DeleteCollisionObject(this);
                    m_isFlying = false;
                    return;
                }

                //岩の位置を更新
                m_transform.m_localPosition = CalcStonePos();

                //岩を回転させる
                m_direction.Add(Vector3(m_rotSpeed, 0.0f, 0.0f));

                //トランスフォームの更新
                m_transform.UpdateTransform();

                //コリジョンの更新
                m_collisionPosition = m_transform.m_position;
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollirionEnemy);

                //モデルの更新
				m_model.SetPosition(m_transform.m_position);
                m_model.SetRotation(m_transform.m_rotation);
                m_model.Update();

                //親クラスの更新処理
                SuperClass::Update();
            }


            void ThrowStone::Render(RenderContext& rc)
            {
                if(m_isFlying) m_model.Draw(rc);
            }


            Vector3 ThrowStone::CalcStonePos()
            {
                m_elapsedTime += g_gameTime->GetFrameDeltaTime();
                float t = m_elapsedTime / m_landingTime;
                Vector3 result = m_startPos + (m_endPos - m_startPos) * t;                
                float posY = std::sin(t * nsK2EngineLow::Math::PI) * m_altitude;
                result.y += posY;

                return result;
            }


            void ThrowStone::SetThrowingInfo(const Vector3& start, const Vector3& end)
            {
                if (m_isFlying) {
                    K2_ASSERT(false, "岩がまだ着地していません");
                    return;
                }
                m_startPos = start;
                m_endPos = end;
                m_collisionObject = CollisionHitManager::Get().CreateCollisionObject(ID(), this, m_collisionPosition, GetRotation(), 20.0f, 0.0f);
                m_elapsedTime = 0.0f;
                m_isFlying = true;
            }
        }
    }
}