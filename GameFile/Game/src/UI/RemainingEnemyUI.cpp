/**
 * RemainingEnemyUI.cpp
 *
 * スコアを計算、管理するクラス
 */
#include "stdafx.h"
#include "RemainingEnemyUI.h"
#include "src/UI/UIBase.h"
#include "src/GameFlow/GameFlowManager.h"


namespace {
    constexpr float NUMBER_WIDE_SIZE = 23.0f;
    constexpr float NUMBER_VERTICAL_SIZE = 40.0f;
    constexpr float MESSAGE_WIDE_SIZE = 350.0f;
    constexpr float MESSAGE_VERTICAL_SIZE = 150.0f;
}


namespace nsApp
{
    namespace nsUI {


        RemainingEnemyUI::RemainingEnemyUI()
        {            
            m_currentPhase = enWaveType_None;
        }


        RemainingEnemyUI::~RemainingEnemyUI()
        {
        }

        bool RemainingEnemyUI::Start()
        {
            //キャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(-770.0f, 450.0f, 0.0f);

            //ベースの枠
            auto* base = m_uiCanvas->CreateUI<ImageUI>();
            base->Initialize("Assets/UI/Instructions/Base.dds", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //光る枠
            m_lightFrame = m_uiCanvas->CreateUI<ImageUI>();
            m_lightFrame->Initialize("Assets/UI/Instructions/Light.dds", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

            //エネミーの残数
            m_enemyCount = m_uiCanvas->CreateUI<NumberUI>();
            m_enemyCount->Initialize("Assets/UI/Numbers/Classic", 0, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE, Vector3(110.0f, -35.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //ウェーブ数
            m_wave = m_uiCanvas->CreateUI<NumberUI>();
            m_wave->Initialize("Assets/UI/Numbers/Classic", 0, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE, Vector3(60.0f, 33.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //状況ごとのメッセージ
            m_massage = m_uiCanvas->CreateUI<ImageUI>();
            m_massage->Initialize("Assets/UI/Instructions", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

            return true;
        }


        void RemainingEnemyUI::Update()
        {
            uint8_t waveNum = nsFlow::GameFlowManager::GetInstance()->GetWaveCount();
            const uint8_t phaseType = nsFlow::GameFlowManager::GetInstance()->GetGameFlow();
            const EnWaveType waveType = nsFlow::GameFlowManager::GetInstance()->GetWaveType();

            //ウェーブ数更新
            if (phaseType == enBattle) {
                m_wave->NumberUpdate("Assets/UI/Numbers/Classic", waveNum, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE);
            }
            else if (phaseType == enPreparation) {
                m_wave->NumberUpdate("Assets/UI/Numbers/Classic", waveNum + 1, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE);
            }


            //残数を更新
            if (phaseType == enBattle && waveType == enWaveType_Normal) {
                m_enemyCount->NumberUpdate("Assets/UI/Numbers/Classic", m_count, NUMBER_WIDE_SIZE, NUMBER_VERTICAL_SIZE);
                m_enemyCount->SetDraw(true);
            }
            else m_enemyCount->SetDraw(false);


            //フェーズが切り替わったかチェック
            if (phaseType != m_currentPhase) {

                //フェーズをセット
                m_currentPhase = phaseType;

                //フェーズに応じて、メッセージをかえる
                switch (phaseType) {

                    case enBattle:
                    {
                        if (waveType == enWaveType_Normal) {
                            m_massage->Initialize("Assets/UI/Instructions/ZOMBIES REMAINING.dds", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);
                        }
                        else if (waveType == enWaveType_Boss) {
                            m_massage->Initialize("Assets/UI/Instructions/DEFEAT BOSS!!.dds", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);
                        }

                        m_lightFrame->SetMulColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));

                        break;
                    }

                    case enPreparation:
                    {
                        m_massage->Initialize("Assets/UI/Instructions/GET READY.dds", MESSAGE_WIDE_SIZE, MESSAGE_VERTICAL_SIZE, Vector3::Zero, Vector3::One, Quaternion::Identity);

                        m_lightFrame->SetMulColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));

                        break;
                    }
                }
            }

            m_uiCanvas->Update();
        }


        void RemainingEnemyUI::Render(RenderContext& rc)
        {
            m_uiCanvas->Render(rc);
        }
    }
}