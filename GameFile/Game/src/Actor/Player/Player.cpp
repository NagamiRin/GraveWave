/**
 * Player.cpp
 *
 * プレイヤーのクラス
 */
#include "stdafx.h"
#include "Player.h"
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
				SetLocalPosition(Vector3(0.0f, 50.0f, 0.0f));
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
				//方向を設定
				SetDirection(Vector3(0.0f, 0.0f, 1.0f));
				//初期位置を設定
				SetLocalPosition(Vector3(0.0f, 150.0f, 0.0f));

				//ハンドガンを生成
				m_handGun = NewGO<nsApp::nsActor::nsGun::HandGun>(enGameObjectPriority_Gun, "HandGun");

				return true;
			}


			void Player::Update()
			{
				UpdateInputLStick();
				PlayerDirectionUpdate();
				JudgOnFire();
				m_stateMachine->Update();

				SuperClass::Update();

				//銃に弾の射出方向を教える
				m_handGun->SetInjectionDirection(GetDirection());
				Vector3 hoge = GetDirection();
			}


			void Player::Render(RenderContext& rc)
			{
			}


			void Player::UpdateInputLStick()
			{
				/** 左スティックの入力量を取得 */
				float InputXDir = g_pad[0]->GetLStickXF();
				/** 入力量をステートマシンに渡す */
				m_stateMachine->SetLStickXDirAmount(InputXDir);
			}


			void Player::PlayerDirectionUpdate()
			{
				static Vector3 dir = Vector3::Front;
				auto* pad = g_pad[0];

				const float xRot = pad->GetRStickXF();
				{
					Quaternion q;
					q.SetRotation(Vector3::Up, xRot * 0.05f);
					q.Apply(dir);
				}
				const float yRot = pad->GetRStickYF();
				{
					Vector3 vec = Vector3::Down;
					vec.Cross(dir);
					Quaternion q;
					q.SetRotation(vec, yRot * 0.05f);
					q.Apply(dir);
				}

				SetDirection(dir);
			}


			void Player::JudgOnFire()
			{
				if (g_pad[0]->IsTrigger(enButtonRB2)) {
					m_handGun->SetPosition(GetPosition());
					m_handGun->OnFire();
					SoundManager::Get().PlaySE(enSoundKind_HandGun_Fire);
					EffectManager::Get().PlayEffect(enEffectKind_Fire, GetPosition()+(GetDirection() * 30.0f), GetRotation(), Vector3::One);
				}
			}
		}		
	}
}