/**
 * Player.h
 * 
 * プレイヤークラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsPlayer
		{
			/**
			 * プレイヤークラス
			 */
			class Player : public CharacterBase
			{
			public:
				/** コンストラクタ */
				Player();
				/** デストラクタ */
				~Player();


			public:
				/** 生成時に一度だけ呼ばれる関数。 */
				bool Start()override;
				/** 毎フレーム呼ばれる更新処理。 */
				void Update()override;
				/** 描画処理。 */
				void Render(RenderContext& rc)override;
			};
		}		
	}
}