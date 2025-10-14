/**
 * Player.h
 * 
 * プレイヤークラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"
#include "PlayerStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			/** 
			 *プレイヤークラス 
			 */
			class Player : public CharacterBase
			{
			private:
				/** プレイヤーステータス */
				int m_hp;

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
				PlayerStatus* GetPlayerStatus() { return dynamic_cast<PlayerStatus*>(m_status); }
			};
		}		
	}
}