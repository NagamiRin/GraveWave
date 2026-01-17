/**
 * Inventory.cpp
 *
 * プレイヤーのインベントリクラス
 */
#include "stdafx.h"
#include "src/Battle/Inventory.h"


namespace nsApp
{
    namespace nsBattle
    {
        Inventory* Inventory::m_instance = nullptr;

        Inventory::Inventory()
        {
            //todo for test
            m_mainWeaponAmmo = 500;
        }

        
        Inventory::~Inventory()
        {
        }     
        
        
        void Inventory::Update()
        {
           
        }       
    }
}