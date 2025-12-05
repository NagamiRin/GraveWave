/**
 * FogObject.h
 *
 * フォグのためのボックスオブジェクト
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
			 * フォグのためのボックスオブジェクトクラス
			 */
			class FogObject : public Actor
			{
			private:

			public:
				FogObject();
				~FogObject();


			public:
				bool Start()override;
				void Update()override;
				void Render(RenderContext& rc)override;
			};
		}
	}
}


