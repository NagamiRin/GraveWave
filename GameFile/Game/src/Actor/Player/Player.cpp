/**
 * Player.cpp
 *
 * プレイヤーのクラス
 */
#include "stdafx.h"
#include "Player.h"
#include "src/Actor/Gun/GunBase.h"
#include "src/Actor/Gun/SubWeapon.h"
#include "src/Actor/Gun/MainWeapon.h"
#include "src/Actor/Player/PlayerStateMachine.h"
#include "src/Core/BattleManager.h"


namespace {
	const Vector3 PLAYER_NEW_POSITION = Vector3{ 0.0f,150.0f,0.0f };
}

namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			Player::Player()
			{
				//ステータス生成
				m_status = new PlayerStatus();
				m_status->Setup();

				//ステートマシン生成
				m_stateMachine = std::make_unique<PlayerStateMachine>();
				m_stateMachine->Setup(this);

				//サブ武器を生成
				m_subWeapon = NewGO<nsGun::SubWeapon>(enGameObjectPriority_Gun, "SubWeapon");
				m_subWeapon->SetParent(&m_transform);
				m_subWeapon->SetIsEquipment(false);


				//メイン武器を生成
				m_mainWeapon = NewGO<nsGun::MainWeapon>(enGameObjectPriority_Gun, "MainWeapon");
				m_mainWeapon->SetParent(&m_transform);
				m_mainWeapon->SetIsEquipment(false);


				//装備武器をサブ武器に設定
				m_subWeapon->SetPossession(true);
				m_mainWeapon->SetPossession(true);
				m_equipmentGun = m_subWeapon;
				m_equipmentGun->SetIsEquipment(true);
				m_equipType = enWeaponType_Sub;
				
				//向きの限界値を設定
				m_verticalLimitAngle = nsCore::BattleManager::GetInstance()->GetVerLimitAngle();
				m_horizontalLimitAngle = nsCore::BattleManager::GetInstance()->GetHorLimitAngle();
			}


			Player::~Player()
			{
				//ステータス削除
				delete m_status;
				m_status = nullptr;

				//ハンドガン削除
				DeleteGO(m_equipmentGun);
			}


			bool Player::Start()
			{
				//初期位置を設定
				SetLocalPosition(PLAYER_NEW_POSITION);
				//初期方向を設定
				SetDirection(Vector3::Front);

				return true;
			}


			void Player::Update()
			{
				//Lスティックの入力を更新
				UpdateInputLStick();
				//右トリガーの入力を更新
				JudgOnFire();
				//ADSの入力を更新
				OnInputADS();
				m_equipmentGun->SetADS(m_isInputADS);
				//武器切り替えの入力を更新
				JudgeToChange();
				//リロードの入力を更新
				JudgeToReload();
				//プレイヤーの向きを更新
				PlayerDirectionUpdate();

				//ステートマシンの更新
				m_stateMachine->Update();

				//親クラスの更新
				SuperClass::Update();

				//銃にプレイヤーの位置を教える
				m_equipmentGun->InformationUpdate(m_transform.m_position, m_direction);		
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
				//右スティックの入力を受け付け、プレイヤーの向きを変える
				static Vector3 dir = Vector3::Front;
				auto* pad = g_pad[0];

				//X軸回転を計算
				const float xRot = pad->GetRStickXF();
				{
					Quaternion q;
					q.SetRotation(Vector3::Up, xRot * 0.02f);
					q.Apply(dir);
				}
				//Y軸回転を計算
				const float yRot = pad->GetRStickYF();
				{
					Vector3 vec = Vector3::Down;
					vec.Cross(dir);
					Quaternion q;
					q.SetRotation(vec, yRot * 0.02f);
					q.Apply(dir);
				}

				dir.Normalize();

				//垂直方向に限界値を設ける
				dir.y = min(dir.y, m_verticalLimitAngle);
				dir.y = max(dir.y, -m_verticalLimitAngle);

				//後ろに向けないようにする
				dir.z = max(dir.z, m_horizontalLimitAngle);

				dir.Normalize();

				//方向をセット
				SetDirection(dir);
			}


			void Player::JudgOnFire()
			{
				//射撃入力を受け付ける
				if (g_pad[0]->IsTrigger(enButtonRB2)) {
					m_equipmentGun->SetPosition(GetPosition());
					m_equipmentGun->OnFire();
				}
			}


			void Player::OnInputADS()
			{
				m_isInputADS = g_pad[0]->IsPress(enButtonLB2);
			}


			void Player::JudgeToChange()
			{
				if (!g_pad[0]->IsTrigger(enButtonLB1)) return;
				if(m_mainWeapon->IsPossession()) m_stateMachine->SetSwitchingWeapon(true);
			}


			void Player::JudgeToReload()
			{
				if (g_pad[0]->IsTrigger(enButtonX)) {
					m_equipmentGun->Reload();
				}
			}			


			void Player::RequestChangeGun(const uint32_t gunID)
			{				
				m_requestGunID = gunID;
				m_stateMachine->SetSwitchingWeapon(true);				
			}


			nsGun::GunBase* Player::ChangeGun()
			{
				//装備している銃が
				//メイン武器ならサブ武器へ
				if (m_equipmentGun == m_mainWeapon) {
					m_equipmentGun = m_subWeapon;
					m_equipType = enWeaponType_Sub;
				}
				//サブ武器ならメイン武器へ
				else if (m_equipmentGun == m_subWeapon) {
					m_equipmentGun = m_mainWeapon;
					m_equipType = enWeaponType_Main;
				}

				return m_equipmentGun;
			}			
		}
	}
}