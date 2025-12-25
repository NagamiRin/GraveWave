/**
 * CaveatUI.cpp
 *
 * クロスヘアの描画
 */
#include "stdafx.h"
#include "CaveatUI.h"
#include "src/UI/UIBase.h"
#include "src/GameFlow/GameFlowManager.h"


namespace {
}


namespace nsApp
{
    namespace nsUI
    {
        CaveatUI::CaveatUI()
        {
            //todo for test
            m_drawCaveatPos = 300.0f;
        }

        
        CaveatUI::~CaveatUI()
        {
        }

       
        bool CaveatUI::Start()
        {
            //キャンバス生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;            

            return true;
        }

        
        void CaveatUI::Update()
        {
            std::vector<CaveatInformation*> deleteList;

            //警告を表示
            for (auto& caveat : m_caveats) {
                if (!caveat.isUpdate) {
                    deleteList.push_back(&caveat);
                    continue;
                }

                UpdateBlinkIcon(caveat);
                Vector2 pos = CalcCaveatPos(caveat);
                caveat.m_icon->SetPosition(Vector3(pos.x, pos.y, 0.0f));
                
                caveat.isUpdate = false;  // 更新フラグをリセット
            }

            for (auto* deleteTarget : deleteList) {
                // 削除リストをもとにアイコン情報を削除
                auto it = std::find_if(m_caveats.begin(), m_caveats.end(), [deleteTarget](const CaveatInformation& info)
                    {
                        return info.m_caveatId == deleteTarget->m_caveatId;
                    });
                m_uiCanvas->Remove(it->m_icon);
                if (it != m_caveats.end()) {
                    m_caveats.erase(it);
                }
            }

            m_uiCanvas->Update();
        }

        
        void CaveatUI::Render(RenderContext& rc)
        {
            if (nsFlow::GameFlowManager::GetInstance()->GetGameFlow() != enBattle) return;

            m_uiCanvas->Render(rc);
        }


        void CaveatUI::UpdateCaveatInformation(const uint64_t iconId, const uint32_t id, const Vector3& position)
        {
            auto* findInfo = FindInformation(iconId);
            if (findInfo == nullptr) {
                CaveatInformation info;
                info.m_caveatId = iconId;
                info.m_id = id;
                info.m_position = position;
                Vector2 iconPos = CalcCaveatPos(info);
                info.m_icon = m_uiCanvas->CreateUI<ImageUI>();
                info.m_icon->Initialize("Assets/UI/Caveat/!.dds", 10.0f, 40.0f, Vector3(iconPos.x, iconPos.y,0.0f), Vector3::One, Quaternion::Identity);
                info.m_icon->SetMulColor(Vector4::Red);
                info.isUpdate = true;
                m_caveats.push_back(std::move(info));
                return;
            }
            findInfo->m_position = position;
            findInfo->isUpdate = true;
        }


        Vector2 CaveatUI::CalcCaveatPos(CaveatInformation& info)
        {
            Vector2 caveatPos = Vector2::Zero;
            g_camera3D->CalcScreenPositionFromWorldPosition(caveatPos, Vector3(info.m_position.x, info.m_position.y + 60.0f, info.m_position.z));

            return caveatPos;
        }


        void CaveatUI::UpdateBlinkIcon(CaveatInformation& info)
        {
            info.m_blinkSwitcher.Update();
            info.m_icon->SetIsDraw(info.m_blinkSwitcher.m_isVisible);
        }
    }
}