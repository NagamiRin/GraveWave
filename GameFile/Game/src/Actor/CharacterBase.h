/**
 * CharacterBase.h
 * 
 * キャラクターのベース
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		/**
		 * キャラクターの基底クラス
		 */
		class CharacterBase :public Actor
		{
			using SuperClass = Actor;


		protected:
			/** コリジョンの位置 */
			Vector3 m_collisionPosition = Vector3::Zero;

		public:
			/** コンストラクタ */
			CharacterBase();
			/** デストラクタ */
			virtual ~CharacterBase();


		public:
			/** 生成時に一度だけ呼ばれる関数 */
			virtual bool Start()override;
			/** 毎フレーム呼ばれる更新処理 */
			virtual void Update()override;
			/** 描画処理 */
			virtual void Render(RenderContext& rc)override;
		};
	}
}