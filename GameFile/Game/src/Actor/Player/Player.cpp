/**
 * Player.cpp
 *
 * プレイヤーのクラス
 */
#include "stdafx.h"
#include "src/Actor/Player/Player.h"
#include "src/Actor/Player/PlayerStateMachine.h"
#include "src/Actor/Gun/HandGun.h"
#include "src/Sound/SoundManager.h"
#include "src/Effect/EffectManager.h"


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

				m_stateMachine = std::make_unique<PlayerStateMachine>();
				m_stateMachine->Setup(this);

				//初期位置設定
				SetPosition(Vector3(10.0f, 10.0f, -100.0f));
				// 初期向き設定
				m_direction = Vector3::Front;
				
			}


			Player::~Player()
			{
				delete m_status;
				m_status = nullptr;
			}


			bool Player::Start()
			{
				//ハンドガンを生成
				m_handGun = NewGO<nsApp::nsActor::nsGun::HandGun>(enGameObjectPriority_Gun, "HandGun");

				return true;
			}


			void Player::Update()
			{
				UpdateInputLStick();
				UpdateInputRStick();
				JudgOnFire();
				m_stateMachine->Update();

				SuperClass::Update();
			}


			void Player::Render(RenderContext& rc)
			{
			}


			void Player::UpdateInputLStick()
			{
				/** 左スティックの入力方向を取得 */
				const Vector3 stickDirection = Vector3(g_pad[0]->GetLStickXF(), 0.0f, g_pad[0]->GetLStickYF());
				/** 入力方向をステートマシンに渡す */
				m_stateMachine->SetLStickDirection(stickDirection);
				/** 左スティックの入力量を計算 */
				const float stickPower = stickDirection.Length();
				/** 入力量をステートマシンに渡す */
				m_stateMachine->SetLStickPower(stickPower);
			}


			void Player::UpdateInputRStick()
			{
				/** 右スティックの入力量を取得 */
				m_inputRStick = Vector2(g_pad[0]->GetRStickXF(), g_pad[0]->GetRStickYF());
			}


			void Player::JudgOnFire()
			{
				if (g_pad[0]->IsTrigger(enButtonRB2) && m_handGun->GetFireCoolTime() <= 0.0f) {
					m_handGun->SetPosition(GetPosition());
					m_handGun->OnFire();
					SoundManager::Get().PlaySE(enSoundKind_HandGun_Fire);
					EffectManager::Get().PlayEffect(enEffectKind_Fire, GetPosition()+(GetDirection() * 30.0f), GetRotation(), Vector3::One);
				}
			}
		}		
	}
}