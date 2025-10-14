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
			class HandGun;
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
				/** ハンドガンのポインタ */
				nsApp::nsActor::nsGun::HandGun* m_handGun = nullptr;


			private:
				/** プレイヤーステータス */
				int m_hp = 0;
				/** プレイヤーのステートマシンのポインタ */
				std::unique_ptr<PlayerStateMachine> m_stateMachine;
				/** RLスティックの入力量 */
				Vector2 m_inputRStick = Vector2::Zero;
				/** 右トリガーの入力情報 */
				bool m_isInputRTrigger = false;


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
				/** Rスティックの入力量を更新 */
				void UpdateInputRStick();
				/** Rトリガーの入力情報を更新 */
				void JudgOnFire();


			public:
				/** プレイヤーのステータスをキャスト */
				PlayerStatus* GetStatus() { return dynamic_cast<PlayerStatus*>(m_status); }

				/** プレイヤーのLスティックの入力量を取得 */
				Vector2 GetInputRStick() const { return m_inputRStick; };

				/** プレイヤーの右トリガーの入力情報を取得 */
				bool GetInputRTrigger()const { return m_isInputRTrigger; }
			};
		}		
	}
}