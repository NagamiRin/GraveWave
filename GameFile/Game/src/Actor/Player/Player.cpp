/**
 * Player.cpp
 *
 * プレイヤーのクラス
 */
#include "stdafx.h"
#include "Player.h"
#include "src/Actor/Player/PlayerStateMachine.h"
#include "src/Actor/Gun/GunBase.h"
#include "src/Actor/Gun/SubWeapon.h"
#include "src/Actor/Gun/MainWeapon.h"
#include "src/Core/BattleManager.h"


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

				m_verticalLimitAngle = nsCore::BattleManager::GetInstance()->GetVerLimitAngle();
				m_horizontalLimitAngle = nsCore::BattleManager::GetInstance()->GetHorLimitAngle();
			}


			Player::~Player()
			{
				//ステータス削除
				delete m_status;
				m_status = nullptr;

				//ハンドガン削除
				DeleteGO(m_gun);
			}


			bool Player::Start()
			{
				//初期位置を設定
				SetLocalPosition(Vector3(0.0f, 150.0f, 10.0f));
				//初期方向を設定
				SetDirection(Vector3::Front);

				//初期装備
				m_gun = NewGO<nsGun::SubWeapon>(enGameObjectPriority_Gun, "HandGun");
				m_gun->SetIsEquipment(true);
				m_gun->SetParent(&m_transform);				

				return true;
			}


			void Player::Update()
			{
				UpdateInputLStick();
				PlayerDirectionUpdate();
				JudgOnFire();
				JudgeToReload();
				m_stateMachine->Update();

				SuperClass::Update();

				//銃にプレイヤーの位置を教える
				m_gun->InformationUpdate(m_transform.m_position, m_direction);
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
					q.SetRotation(Vector3::Up, xRot * 0.02f);
					q.Apply(dir);
				}
				const float yRot = pad->GetRStickYF();
				{
					Vector3 vec = Vector3::Down;
					vec.Cross(dir);
					Quaternion q;
					q.SetRotation(vec, yRot * 0.02f);
					q.Apply(dir);
				}
				dir.Normalize();

				dir.y = min(dir.y, m_verticalLimitAngle);
				dir.y = max(dir.y, -m_verticalLimitAngle);
				dir.z = max(dir.z, m_horizontalLimitAngle);

				dir.Normalize();

				SetDirection(dir);
			}


			void Player::JudgOnFire()
			{
				if (g_pad[0]->IsTrigger(enButtonRB2)) {
					m_gun->SetPosition(GetPosition());
					m_gun->OnFire();
				}
			}


			void Player::JudgeToReload()
			{
				if (g_pad[0]->IsTrigger(enButtonX)) {
					m_gun->Reload();
				}
			}			


			void Player::RequestChangeGun(const uint32_t gunID)
			{
				
				m_requestGunID = gunID;
				m_stateMachine->SetSwitchingWeapon(true);
				
			}


			nsGun::GunBase* Player::ChangeGun()
			{
				DeleteGO(m_gun);

				nsGun::GunBase* createGun = nullptr; 

				//サブ武器
				if (m_requestGunID == nsGun::SubWeapon::ID()) {
					createGun = NewGO<nsGun::SubWeapon>(enGameObjectPriority_Gun, "SubWeapon");
				}

				//メイン武器
				else if (m_requestGunID == nsGun::MainWeapon::ID()) {
					createGun = NewGO<nsGun::MainWeapon>(enGameObjectPriority_Gun, "MainWeapon");
				}

				else
				{
					K2_ASSERT(false, "存在しない銃IDが指定されました");
					// 一応デフォルトでハンドガンを生成
					createGun = NewGO<nsGun::SubWeapon>(enGameObjectPriority_Gun, "SubWeapon");
				}

				// 切り替え
				m_gun = createGun;

				//親設定
				m_gun->SetParent(&m_transform);


				return createGun;
			}
		}
	}
}