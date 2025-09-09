/**
 * EnemyBase.cpp
 *
 * エネミーの基底クラス
 */
#include "stdafx.h"
#include "src/Actor/Enemy/EnemyBase.h"


namespace nsApp
{
	namespace nsActor
	{
		EnemyBase::EnemyBase()
		{
		}


		EnemyBase::~EnemyBase()
		{
		}


		bool EnemyBase::Start()
		{
			return true;
		}


		void EnemyBase::Update()
		{
		}


		void EnemyBase::Render(RenderContext& rc)
		{
		}
	}
}