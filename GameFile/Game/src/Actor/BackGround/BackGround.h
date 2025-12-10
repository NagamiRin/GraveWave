/**
 * BackGround.h
 *
 * 背景オブジェクト
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBackGround
		{
			/**
			 * 背景オブジェクト
			 */
			class BackGround : public Actor
			{
				appGameObject(BackGround);


			private:
				PhysicsStaticObject* m_physicsStaticObject = nullptr;

			public:
				/** コンストラクタ */
				BackGround();
				/** デストラクタ */
				~BackGround();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				bool Start()override;
				/** 毎フレーム呼び出される関数 */
				void Update()override;
				/** モデルの描画処理を行う関数 */
				void Render(RenderContext& rc)override;
			};
		}
	}
}


