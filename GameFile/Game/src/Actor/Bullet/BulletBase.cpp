/**
 * BulletBase.cpp
 *
 * 弾の基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Bullet/BulletBase.h"
#include "src/Collision/CollisionManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			BulletBase::BulletBase()
			{
			}


			BulletBase::~BulletBase()
			{
			}


			bool BulletBase::Start() 
			{
				return true;
			}


			void BulletBase::Update()
			{

			}


			void BulletBase::Render(RenderContext& rc)
			{

			}
		}
	}
}