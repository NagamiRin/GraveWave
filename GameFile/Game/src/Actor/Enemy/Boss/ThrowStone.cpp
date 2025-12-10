/**
 * ThrowStone.cpp
 *
 * ボスが投げる岩クラス
 */
#include "stdafx.h"
#include "ThrowStone.h"
#include "src/Actor/Enemy/Boss/BreakStone.h"
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
                        p.m_divisionNum = j["DivisionNum"].get<uint8_t>();
                    });

                auto* param = ParameterManager::Get().GetParameter<MasterStoneParameter>();

                m_altitude = param->m_altitude;
                m_landingTime = param->m_landingTime;
                m_rotSpeed = param->m_rotSpeed;
                m_maxDurability = param->m_maxDurability;
                m_divisionNum = param->m_divisionNum;
            }


            ThrowStone::~ThrowStone()
            {
                ParameterManager::Get().UnloadParameter<MasterStoneParameter>();
            }


            bool ThrowStone::Start()
            {
                m_model.Init("Assets/ModelData/Zombie/Boss/Stone.tkm");

                return true;
            }
            

            void ThrowStone::Update()
            {
                //飛翔中でないなら処理しない
                if (!m_isFlying) return;
                //耐久度がなくなった、もしくは着地時間になったら破壊処理
                if (m_durability <= 0 || m_elapsedTime >= m_landingTime) {
                    BreakProcess();
                    return;
                }



                //岩の位置を更新
                m_transform.m_localPosition = CalcStonePos();

                //岩を回転させる
                m_transform.m_localRotation.AddRotationX(m_rotSpeed);

                //トランスフォームの更新
                m_transform.UpdateTransform();

                //コリジョンの更新
                m_collisionPosition = m_transform.m_position;
                m_collisionObject->SetPosition(m_collisionPosition);
                m_collisionObject->Update();

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


            void ThrowStone::BreakProcess()
            {
                /** 破片を出す */
                for (uint8_t i = 0; i < m_divisionNum; i++) {
                    auto* breakStone = NewGO<BreakStone>(enGameObjectPriority_Enemy, "BreakStone");
                    breakStone->SetLocalPosition(m_transform.m_localPosition);
                }

                if (!CollisionHitManager::Get().CheckCollision(this)) return;
                CollisionHitManager::Get().DeleteCollisionObject(this);
                m_isFlying = false;
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
                m_collisionObject->GetbtCollisionObject().setUserIndex(nsApp::enCollirionStone);
                m_elapsedTime = 0.0f;
                m_durability = m_maxDurability;
                m_isFlying = true;
            }
        }
    }
}