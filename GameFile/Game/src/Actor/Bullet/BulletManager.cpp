/**
 * BulletManager.cpp
 *
 * 弾管理クラス
 */
#include "stdafx.h"
#include "src/Actor/Bullet/BulletManager.h"
#include "src/Actor/Bullet/NormalBullet.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			BulletManager* BulletManager::m_instance = nullptr;

			BulletManager::BulletManager()
			{
			}


			BulletManager::~BulletManager()
			{
				for (int i = 0; i < m_normalBulletList.size(); i++) {
					auto* bullet = m_normalBulletList[i];
					DeleteGO(bullet);
				}
				m_normalBulletList.clear();
			}			


			void BulletManager::Setup()
			{

			}			


			void BulletManager::Update()
			{
				NaturalDelete();
			}			


			void BulletManager::NaturalDelete()
			{
				//通常弾削除
				for(int i=0;i<m_normalBulletList.size();i++) {
					auto* bullet = m_normalBulletList.at(i);
					float hoge = bullet->GetCurrentFlyTime();
					if (bullet->GetCurrentFlyTime() >= 5.0f) {
						
						DeleteGO(bullet);
						m_normalBulletList.erase(m_normalBulletList.begin() + i);
						i--;
					}
				}
			}
		}
	}
}