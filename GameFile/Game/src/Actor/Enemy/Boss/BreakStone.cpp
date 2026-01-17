/**
 * BreakStone.cpp
 *
 * 岩の破壊表現を行うクラス
 */
#include "stdafx.h"
#include "BreakStone.h"
#include "src/Collision/CollisionManager.h"
#include "src/Core/ParameterManager.h"


namespace {
    constexpr float GRAVITY_AMOUNT = 9.8f;
    const Vector3 NEW_SCALE = Vector3{ 0.2f,0.2f,0.2f };
}


namespace nsApp
{
    namespace nsActor
    {
        namespace nsEnemy
        {
            BreakStone::BreakStone()
            {
                ParameterManager::Get().LoadParameter<MasterBreakStoneParameter>("Assets/Parameter/StoneBreakParameter.json", [](const nlohmann::json& j, MasterBreakStoneParameter& p)
                    {
                        p.m_altitude = j["Altitude"].get<float>();
                        p.m_landingTime = j["LandingTime"].get<float>();
                        p.m_rotSpeed = j["RotSpeed"].get<float>();                        
                    });

                auto* param = ParameterManager::Get().GetParameter<MasterBreakStoneParameter>();

                m_altitude = param->m_altitude;
                m_landingTime = param->m_landingTime;
                m_rotSpeed = param->m_rotSpeed;
            }


            BreakStone::~BreakStone()
            {
                ParameterManager::Get().UnloadParameter<MasterBreakStoneParameter>();
            }


            bool BreakStone::Start()
            {
                m_model.Init("Assets/ModelData/Zombie/Boss/Stone.tkm");

                m_transform.m_localScale = Vector3(NEW_SCALE);

                Quaternion q;
                q.SetRotationX(static_cast<float>(GetRand() % 360));
                q.SetRotationY(static_cast<float>(GetRand() % 360));
                q.SetRotationZ(static_cast<float>(GetRand() % 360));

                m_model.SetRotation(q);

                m_velocity = GetForce();

                return true;
            }
            

            void BreakStone::Update()
            {
                const float deltaTime = g_gameTime->GetFrameDeltaTime();
                m_velocity.y -= GRAVITY_AMOUNT * deltaTime;
                m_transform.m_localPosition += m_velocity;

                //着地したらdelete
                if (m_transform.m_localPosition.y < 0.0f) {
                    DeleteGO(this);
                }

                //岩を回転させる
                m_transform.m_localRotation.AddRotationX(m_rotSpeed);

                //トランスフォームの更新
                m_transform.UpdateTransform();

                //モデルの更新
				m_model.SetPosition(m_transform.m_position);
                m_model.SetRotation(m_transform.m_rotation);
                m_model.Update();

                //親クラスの更新処理
                SuperClass::Update();
            }


            void BreakStone::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }


            uint32_t BreakStone::GetRand()
            {
                std::srand(std::time(nullptr) + std::rand());
                return std::rand();
            }


            Vector3& BreakStone::GetForce()
            {
                // 現在の時間をseed値にして、良い感じのランダムになるようにする
                float angle = static_cast<float>(GetRand() % 360);
                // 求めた角度を使ってY軸回転する
                // 岩が飛ぶ方向を求める
                Vector3 direction = Vector3::Front;
                Quaternion q;
                q.SetRotationY(angle);
                q.Apply(direction);
                // 求めた方向を使って飛ぶ力を与える
                Vector3 force = direction;
                force.y = 1.0f;
                // ここを調整
                constexpr float POWER_XZ = 4.0f;
                constexpr float POWER_Y = 2.0f;
                force.x *= POWER_XZ;
                force.y *= POWER_Y;
                force.z *= POWER_XZ;

                return force;
            }
        }
    }
}