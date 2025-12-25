/**
 * MiniMapUI.cpp
 *
 * カウントダウンUIの描画
 */
#include "stdafx.h"
#include "MiniMapUI.h"
#include "src/UI/UIBase.h"
#include "src/GameFlow/GameFlowManager.h"


namespace {
    constexpr float CANVAN_POSX = -770.0f;
    constexpr float CANVAN_POSY = -290.0f;
}


namespace nsApp
{
    namespace nsUI
    {
        MiniMapUI::MiniMapUI()
        {
        }

        
        MiniMapUI::~MiniMapUI()
        {
        }

       
        bool MiniMapUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3(CANVAN_POSX, CANVAN_POSY, 0.0f);
            
            //ミニマップの背景
            ImageUI* back = m_uiCanvas->CreateUI<ImageUI>();
            back->Initialize("Assets/UI/MiniMapUI/MiniMap.dds", 350.0f, 350.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //レーダー
            m_radar = m_uiCanvas->CreateUI<ImageUI>();
            m_radar->Initialize("Assets/UI/MiniMapUI/Radar.dds", 155.0f, 155.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);
            m_radar->SetPivot(Vector2(0.0f, 0.0f));
            m_radar->SetMulColor(Vector4(0.3f,1.0f,0.3f,0.4f));

            //ボスのアイコン
            m_bossIcon.m_icon = m_uiCanvas->CreateUI<ImageUI>();
            m_bossIcon.m_icon->Initialize("Assets/UI/MiniMapUI/BossIcon.dds", 30.0f, 30.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            m_bossIcon.m_icon->SetMulColor(Vector4::Red);                

            m_uiCanvas->Update();
        
            return true;
        }

        
        void MiniMapUI::Update()
        {
            //レーダーを回す
            static Quaternion rot;
            rot.AddRotationDegZ(5.0f);
            m_radar->SetRotation(rot);


            std::vector<EnemyIconInformation*> deleteList;

            //エネミーのアイコンを表示
            for (auto& icon : m_enemyIcons) {
                if (!icon.m_isUpdate) {
                    deleteList.push_back(&icon);
                    continue;
                }
                icon.m_icon->SetPosition(Vector3(icon.m_position.x * 0.2f, (icon.m_position.z * 0.2f)  -100.0f, 0.0f));
				icon.m_isUpdate = false;  // 更新フラグをリセット
            }

            if (m_bossIcon.m_isAlive) {
                m_bossIcon.m_icon->SetIsDraw(true);
                m_bossIcon.m_icon->SetPosition(Vector3(m_bossIcon.m_position.x * 0.2f, (m_bossIcon.m_position.z * 0.2f) - 100.0f, 0.0f));
            }
            else m_bossIcon.m_icon->SetIsDraw(false);

            
            for (auto* deleteTarget : deleteList) {
                // 削除リストをもとにアイコン情報を削除
                auto it = std::find_if(m_enemyIcons.begin(), m_enemyIcons.end(), [deleteTarget](const EnemyIconInformation& info)
                    {
                        return info.m_iconId == deleteTarget->m_iconId;
                    });
                m_uiCanvas->Remove(it->m_icon);
                if (it != m_enemyIcons.end()) {
                    m_enemyIcons.erase(it);
                }
            }

            m_uiCanvas->Update();
        }

        
        void MiniMapUI::Render(RenderContext& rc)
        {
            //if (nsFlow::GameFlowManager::GetInstance()->GetGameFlow() != enBattle) return;

            m_uiCanvas->Render(rc);
        }


        void MiniMapUI::UpdateIconInformation(const uint64_t iconId, const uint32_t id, const Vector3& position)
        {
            auto* findInfo = FindInformation(iconId);
            if (findInfo == nullptr) {
                EnemyIconInformation info;
                info.m_iconId = iconId;
                info.m_id = id;
                info.m_position = position;
                info.m_icon = m_uiCanvas->CreateUI<ImageUI>();
                info.m_icon->Initialize("Assets/UI/MiniMapUI/EnemyIcon.dds", 10.0f, 10.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                info.m_icon->SetMulColor(Vector4::Red);
                info.m_isUpdate = true;
                m_enemyIcons.push_back(std::move(info));
                return;
            }
            findInfo->m_position = position;
            findInfo->m_isUpdate = true;
        }
    }
}