/**
 * GameCamera.cpp
 *
 * ゲームカメラクラス
 */
#include "stdafx.h"
#include "GameCamera.h"
#include "src/core/ParameterManager.h"


namespace nsApp
{  
    namespace nsCamera
    {
        GameCamera::GameCamera()
        {
            //パラメーター読み込み
            ParameterManager::Get().LoadParameter<MasterCameraParameter>("Assets/Parameter/CameraParameter.json", [](const nlohmann::json& j, MasterCameraParameter& p)
                {
                    p.m_cameraNear = j["CameraNear"].get<float>();
                    p.m_cameraFar = j["CameraFar"].get<float>();
                    p.m_initialCameraPositionX = j["InitialCameraPositionX"].get<float>();
                    p.m_initialCameraPositionY = j["InitialCameraPositionY"].get<float>();
                    p.m_initialCameraPositionZ = j["InitialCameraPositionZ"].get<float>();
                    p.m_initialTargetPositionX = j["InitialTargetPositionX"].get<float>();
                    p.m_initialTargetPositionY = j["InitialTargetPositionY"].get<float>();
                    p.m_initialTargetPositionZ = j["InitialTargetPositionZ"].get<float>();
                    p.m_cameraSensitivity = j["CameraSensitivity"].get<float>();
                });

            //パラメーター設定
            auto* parameter = ParameterManager::Get().GetParameter<MasterCameraParameter>();
            m_cameraNear = parameter->m_cameraNear;
            m_cameraFar = parameter->m_cameraFar;
            m_initialCameraPositionX = parameter->m_initialCameraPositionX;
            m_initialCameraPositionY = parameter->m_initialCameraPositionY;
            m_initialCameraPositionZ = parameter->m_initialCameraPositionZ;
            m_initialTargetPositionX = parameter->m_initialTargetPositionX;
            m_initialTargetPositionY = parameter->m_initialTargetPositionY;
            m_initialTargetPositionZ = parameter->m_initialTargetPositionZ;
            m_cameraSensitivity = parameter->m_cameraSensitivity;

            /** 近平面を設定 */
            g_camera3D->SetNear(m_cameraNear);
            /** 遠平面を設定 */
            g_camera3D->SetFar(m_cameraFar);

            // @TODO：　テスト用
            m_cameraPos = Vector3(m_initialCameraPositionX, m_initialCameraPositionY, -m_initialCameraPositionZ);
            m_targetPos = Vector3(m_initialTargetPositionX, m_initialTargetPositionY, m_initialTargetPositionZ);
            m_cameraDir = Vector3::Front;
        }


        GameCamera::~GameCamera()
        {
            ParameterManager::Get().UnloadParameter<MasterCameraParameter>();
        }


        bool GameCamera::Start()
        {
            return true;
        }


        void GameCamera::Update()
        {
            SetCameraTarget();
            //画面揺れクラスの更新
            m_cameraShake.Update(g_gameTime->GetFrameDeltaTime(), m_cameraPos, m_targetPos);
            CameraUpdate();
        }


        void GameCamera::SetCameraTarget()
        {
            m_targetPos.x = m_cameraPos.x + (m_cameraDir.x * 10.0f);
            m_targetPos.y = m_cameraPos.y + (m_cameraDir.y * 10.0f);
            m_targetPos.z = m_cameraPos.z + (m_cameraDir.z * 10.0f);
        }


        void GameCamera::CameraUpdate()
        {
            // TOOD: 線形補完時間調整予定
            //画角設定
            m_currentViewAngleTime += g_gameTime->GetFrameDeltaTime();
            float rate = m_currentViewAngleTime / 0.1f;
            if (rate >= 1.0f) {
                rate = 0.0f;
            }
            m_cameraViewAngle = Math::Lerp<float>(rate, m_prevCameraViewAngle, m_requestCameraViewAngle);

            g_camera3D->SetViewAngle(m_cameraViewAngle);

            /** カメラ座標を更新 */
            g_camera3D->SetPosition(m_cameraPos);
            //* 注視点を更新 */
            g_camera3D->SetTarget(m_targetPos + m_targetOffsetPos);
            /** カメラを更新 */
            g_camera3D->Update();
        }


        void GameCamera::Render(RenderContext& rc)
        {
        }


        void GameCamera::PlayShake(const ShakeStrength strength, const float durationTime, const float intensity, const float frequency)
        {
            m_cameraShake.StartShake(strength, durationTime, intensity, frequency);
        }
    }
}