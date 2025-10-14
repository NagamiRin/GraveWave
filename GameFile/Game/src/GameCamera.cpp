/**
 * GameCamera.cpp
 *
 * ゲームカメラクラス
 */
#include "stdafx.h"
#include "src/GameCamera.h"


namespace nsApp
{  
    GameCamera::GameCamera()
    {
        /** 近平面を設定 */
        g_camera3D->SetNear(1.0f);
        /** 遠平面を設定 */
		g_camera3D->SetFar(10000.0f);

        // @TODO：　テスト用
        m_cameraPos = Vector3(10.0f, 10.0f, -100.0f);
        m_targetPos = Vector3(10.0f, 10.0f, 0.0f);
    }


    GameCamera::~GameCamera()
    {
    }


    bool GameCamera::Start()
    {
        return true;
    }


    void GameCamera::Update()
    {
        SetCameraTarget();
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
        /** カメラ座標を更新 */
		g_camera3D->SetPosition(m_cameraPos);
        //* 注視点を更新 */
		g_camera3D->SetTarget(m_targetPos);
        /** カメラを更新 */
        g_camera3D->Update();
    }


    void GameCamera::Render(RenderContext& rc)
    {
    }        
}