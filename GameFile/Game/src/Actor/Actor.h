/**
 * Actor.h
 *
 * ゲームオブジェクトのベース
 */
#pragma once


class Transform;

namespace nsApp
{
	namespace nsActor
	{
		/**
		 *ゲームオブジェクトの基底クラス
		 */
		class Actor : public IGameObject
		{
		public:
			/** コンストラクタ */
			Actor();
			/** デストラクタ */
			~Actor();


		public:
			/** オブジェクト生成時に一度だけ実行される関数 */
			virtual bool Start()override = 0;
			/** 毎フレーム呼び出される関数 */
			virtual void Update()override = 0;
			/** モデルの描画処理を行う関数 */
			virtual void Render(RenderContext& rc)override = 0;


		private:
			/** モデル描画用変数  */
			ModelRender m_model;
		};
	}
}


