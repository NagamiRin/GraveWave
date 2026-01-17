/**
 * ShopUI.cpp
 *
 * ショップUIの描画
 */
#include "stdafx.h"
#include "ShopUI.h"
#include "src/UI/UIBase.h"
#include "src/Core/BattleManager.h"
#include "src/Core/ParameterManager.h"
#include "src/GameFlow/GameFlowManager.h"


namespace {
    constexpr float PRICE_STRING_WIDE = 1.0f;               //値段表示の横文字サイズ
    constexpr float PRICE_STRING_HIGHT = 1.0f;              //値段表示の縦文字サイズ
    constexpr float PRICE_STRING_SPACE = 1.0f;              //＄マークとの文字間
}


namespace nsApp
{
    namespace nsUI
    {
        ShopUI::ShopUI()
        {
            ParameterManager::Get().LoadParameter<MasterShopUIParameter>("Assets/Parameter/UI/ShopUIParameter.json", [](const nlohmann::json& j, MasterShopUIParameter& p)
                {
                    p.m_subWeaponPositionX = j["SubWeaponPositionX"].get<float>();
                    p.m_subWeaponPositionY = j["SubWeaponPositionY"].get<float>();
                    p.m_subWeaponWidth = j["SubWeaponWidth"].get<float>();
                    p.m_subWeaponHeight = j["SubWeaponHeight"].get<float>();
                    p.m_mainWeaponPositionX = j["MainWeaponPositionX"].get<float>();
                    p.m_mainWeaponPositionY = j["MainWeaponPositionY"].get<float>();
                    p.m_mainWeaponWidth = j["MainWeaponWidth"].get<float>();
                    p.m_mainWeaponHeight = j["MainWeaponHeight"].get<float>();
                });

            ParameterManager::Get().LoadParameter<MasterShopColumnUIParameter>("Assets/Parameter/UI/ShopUIItemsParameter.json", [](const nlohmann::json& j, MasterShopColumnUIParameter& p)
                {
                    p.m_columnPositionX = j["ColumnPositionX"].get<float>();
                    p.m_columnPositionY = j["ColumnPositionY"].get<float>();
                    p.m_columnWidth = j["ColumnWidth"].get<float>();
                    p.m_columnHeight = j["ColumnHeight"].get<float>();
                    p.m_pricePositionX = j["PricePositionX"].get<float>();
                    p.m_pricePositionY = j["PricePositionY"].get<float>();
                    p.m_price = j["Price"].get<uint16_t>();
                    p.m_itemName = j["ItemName"].get<std::string>();
                });            
        }

        
        ShopUI::~ShopUI()
        {
            ParameterManager::Get().UnloadParameter<MasterShopColumnUIParameter>();
        }

       
        bool ShopUI::Start()
        {
            auto* shopParam = ParameterManager::Get().GetParameter<MasterShopUIParameter>();


            // ショップUI全体の大きなキャンバスを生成
            m_uiCanvas = std::make_unique<UICanvas>();
            m_uiCanvas->m_transform.m_localPosition = Vector3::Zero;

            // ショップ全体の背景
            auto* wholeBack = m_uiCanvas->CreateUI<ImageUI>();
            wholeBack->Initialize("Assets/UI/Shop/IconBack.dds", 1920.0f, 1080.0f, Vector3::Zero, Vector3::One, Quaternion::Identity);
            wholeBack->SetMulColor(Vector4(0.0f, 0.0f, 0.0f, 0.6f));

            //サブウェポン背景
            auto* subWeaponBack = m_uiCanvas->CreateUI<ImageUI>();
            subWeaponBack->Initialize("Assets/UI/Shop/IconBack.DDS", 
                shopParam->m_subWeaponWidth, 
                shopParam->m_subWeaponHeight, 
                Vector3(shopParam->m_subWeaponPositionX, shopParam->m_subWeaponPositionY, 0.0f), 
                Vector3::One, 
                Quaternion::Identity);
            subWeaponBack->SetMulColor(Vector4(0.4f, 0.7f, 0.6f, 0.6f));

            // サブウェポン表示
            auto* subWeapon = m_uiCanvas->CreateUI<ImageUI>();
            subWeapon->Initialize("Assets/UI/Shop/SubWeapon.DDS", 
                shopParam->m_subWeaponWidth,
                shopParam->m_subWeaponHeight,
                Vector3(shopParam->m_subWeaponPositionX, shopParam->m_subWeaponPositionY, 0.0f),
                Vector3::One,
                Quaternion::Identity);
            subWeapon->SetMulColor(Vector4::White);

            //メインウェポン背景
            auto* mainWeaponBack = m_uiCanvas->CreateUI<ImageUI>();
            mainWeaponBack->Initialize("Assets/UI/Shop/IconBack.DDS",
                shopParam->m_mainWeaponWidth,
                shopParam->m_mainWeaponHeight,
                Vector3(shopParam->m_mainWeaponPositionX, shopParam->m_mainWeaponPositionY, 0.0f),
                Vector3::One,
                Quaternion::Identity);
            mainWeaponBack->SetMulColor(Vector4(0.4f, 0.7f, 0.6f, 0.6f));

            // メインウェポン表示
            auto* mainWeapon = m_uiCanvas->CreateUI<ImageUI>();
            mainWeapon->Initialize("Assets/UI/Shop/MainWeapon.DDS", 
                shopParam->m_mainWeaponWidth,
                shopParam->m_mainWeaponHeight,
                Vector3(shopParam->m_mainWeaponPositionX, shopParam->m_mainWeaponPositionY, 0.0f),
                Vector3::One,
                Quaternion::Identity);
            mainWeapon->SetMulColor(Vector4::White);

            // 各商品の背景、アイコン、値段、名前を表示する
            const auto& paramList = ParameterManager::Get().GetParameters<MasterShopColumnUIParameter>();
            for (int i = 0; i < paramList.size(); i++) {
                auto param = paramList.at(i);

                // キャンバス生成
                auto* canvas = m_uiCanvas->CreateUI<UICanvas>();
                canvas->m_transform.m_localPosition = Vector3(param->m_columnPositionX, param->m_columnPositionY, 0.0f);

                // 背景表示
                auto* back = canvas->CreateUI<ImageUI>();
                back->Initialize("Assets/UI/Shop/IconBack.dds", param->m_columnWidth, param->m_columnHeight, Vector3::Zero, Vector3::One, Quaternion::Identity);
                back->SetMulColor(Vector4(0.5f, 0.5f, 0.5f, 0.4f));
                m_uiBackList.push_back(back);

                // アイコン表示
                auto* icon = canvas->CreateUI<ImageUI>();
                std::string iconPath = "Assets/UI/Shop/" + param->m_itemName + ".dds";
                icon->Initialize(iconPath.c_str(), param->m_columnWidth, param->m_columnHeight, Vector3::Zero, Vector3::One, Quaternion::Identity);

                // $マーク表示
                auto* priceMark = canvas->CreateUI<ImageUI>();
                priceMark->Initialize("Assets/UI/Shop/$.dds", PRICE_STRING_WIDE, PRICE_STRING_HIGHT, Vector3(param->m_pricePositionX, param->m_pricePositionY, 0.0f), Vector3::One, Quaternion::Identity);

                // 値段表示
                auto* price = canvas->CreateUI<NumberUI>();
                price->Initialize("Assets/UI/Numbers/Classic", param->m_price, PRICE_STRING_WIDE, PRICE_STRING_HIGHT, Vector3(param->m_pricePositionX + PRICE_STRING_SPACE, param->m_pricePositionY, 0.0f), Vector3::One, Quaternion::Identity);
                price->SetColor(Vector4::White);
            }

            m_uiCanvas->Update();
        
            return true;
        }

        
        void ShopUI::Update()
        {
            m_uiCanvas->Update();
            
            //現在選択している画像の色を変える
            if (m_beforeIndex == m_index) return;
            m_uiBackList[m_index]->SetMulColor(Vector4(0.5f, 0.8f, 0.7f, 0.5f));//ちょっと深めの緑
            m_uiBackList[m_beforeIndex]->SetMulColor(Vector4(0.5f, 0.5f, 0.5f, 0.4f));
            m_beforeIndex = m_index;
        }

        
        void ShopUI::Render(RenderContext& rc)
        {
            if (!m_isOpen) return;

            if(m_isOpen) m_uiCanvas->Render(rc);
        }
    }
}