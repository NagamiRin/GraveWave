/**
 * Player.h
 * 
 * プレイヤークラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"
#include "src/Actor/Player/PlayerStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsGun
		{
			class GunBase;
		}
	}
}

namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			class PlayerStateMachine;


			/** 
			 *プレイヤークラス 
			 */
			class Player : public CharacterBase
			{
				appGameObject(Player);


			private:
				using SuperClass = CharacterBase;
				/** 装備している銃のポインタ */
				nsGun::GunBase* m_gun = nullptr;
				/** 切り替えたい銃のID */
				uint32_t m_requestGunID = INVALID_ID;
				/** プレイヤーのステートマシンのポインタ */
				std::unique_ptr<PlayerStateMachine> m_stateMachine;
				/** RLスティックの入力量 */
				Vector2 m_inputRStick = Vector2::Zero;
				/** 右トリガーの入力情報 */
				bool m_isInputRTrigger = false;
				/** 上下方向の限界値 */
				float m_verticalLimitAngle = 0.0f;
				/** 左右方向の限界値 */
				float m_horizontalLimitAngle = 0.0f;


			private:
				/** プレイヤー向き更新 */
				void PlayerDirectionUpdate();


			public:
				/** コンストラクタ */
				Player();
				/** デストラクタ */
				virtual ~Player();


			public:
				/** 生成時に一度だけ呼ばれる関数。 */
				virtual bool Start()override;
				/** 毎フレーム呼ばれる更新処理。 */
				virtual void Update()override;
				/** 描画処理。 */
				virtual void Render(RenderContext& rc)override;


			public:
				/** Lスティックの入力量を更新 */
				void UpdateInputLStick();
				/** Rトリガーの入力情報を更新 */
				void JudgOnFire();
				/** Xボタンの入力を更新 */
				void JudgeToReload();
				/** 装備する銃をリクエスト */
				void RequestChangeGun(const uint32_t gunID);

				
			public:
				/** プレイヤーのステータスをキャスト */
				inline PlayerStatus* GetStatus() { return dynamic_cast<PlayerStatus*>(m_status); }
				/** プレイヤーのLスティックの入力量を取得 */
				inline Vector2 GetInputRStick() const { return m_inputRStick; };
				/** プレイヤーの右トリガーの入力情報を取得 */
				inline bool GetInputRTrigger() const { return m_isInputRTrigger; }				
				/** 装備している銃を取得 */
				inline nsGun::GunBase* GetGun() const { return m_gun; }
				/** 装備する銃を切り替え */
				nsGun::GunBase* ChangeGun();
			};
		}		
	}
}