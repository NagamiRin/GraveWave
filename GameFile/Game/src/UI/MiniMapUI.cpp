/**
 * MiniMapUI.cpp
 *
 * カウントダウンUIの描画
 */
#include "stdafx.h"
#include "MiniMapUI.h"
#include "src/UI/UIBase.h"


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
            m_uiCanvas->m_transform.m_localPosition = Vector3(-800.0f, 150.0f, 0.0f);
            
            //ミニマップの背景
            ImageUI* back = m_uiCanvas->CreateUI<ImageUI>();
            back->Initialize("Assets/UI/MiniMapUI/Back.dds", 200.0f, 400.0f, Vector3(0.0f, 0.0f, 0.0f), Vector3::One, Quaternion::Identity);

            //防壁のアイコン
            back = m_uiCanvas->CreateUI<ImageUI>();
            back->Initialize("Assets/UI/WallIcon/Back.dds", 90.0f, 20.0f, Vector3(0.0f,180.0f,0.0f), Vector3::One, Quaternion::Identity);
            back->SetMulColor(Vector4::Blue);

            m_uiCanvas->Update();
        
            return true;
        }

        
        void MiniMapUI::Update()
        {
            std::vector<EnemyIconInformation*> deleteList;

            //エネミーのアイコンを表示
            for (auto& icon : m_enemyIcons) {
                if (!icon.isUpdate) {
                    deleteList.push_back(&icon);
                    continue;
                }
                icon.m_icon->SetPosition(Vector3(icon.m_position.x * 0.2f, (icon.m_position.z * 0.2f)  -100.0f, 0.0f));
				icon.isUpdate = false;  // 更新フラグをリセット
            }
            
            for (auto* deleteTarget : deleteList) {
				// 削除リストをもとにアイコン情報を削除
                auto it = std::find_if(m_enemyIcons.begin(), m_enemyIcons.end(),
					[deleteTarget](const EnemyIconInformation& info) { return info.m_iconId == deleteTarget->m_iconId; });
                if (it != m_enemyIcons.end()) {
                    m_enemyIcons.erase(it);
                }
                m_uiCanvas->Remove(deleteTarget->m_icon);
            }

            m_uiCanvas->Update();
        }

        
        void MiniMapUI::Render(RenderContext& rc)
        {
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
                info.m_icon->Initialize("Assets/UI/MiniMapUI/EnemyIcon.dds", 15.0f, 15.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
                info.isUpdate = true;
                m_enemyIcons.push_back(std::move(info));
                return;
            }
            findInfo->m_position = position;
            findInfo->isUpdate = true;
        }
    }
}