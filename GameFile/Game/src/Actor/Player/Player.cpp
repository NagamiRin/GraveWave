/**
 * Player.cpp
 *
 * プレイヤーのクラス
 */
#include "stdafx.h"
#include "src/Actor/Player/Player.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			Player::Player()
			{
				m_status = new PlayerStatus();
				m_status->Setup();
			}


			Player::~Player()
			{
				delete m_status;
				m_status = nullptr;
			}


			bool Player::Start()
			{
				return true;
			}


			void Player::Update()
			{
			}


			void Player::Render(RenderContext& rc)
			{
			}
		}		
	}
}