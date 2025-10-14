/**
 * Crosshair.h
 *
 * クロスヘアの描画
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class Crosshair:public IGameObject
		{
		private:
			/**画像モデル*/
			SpriteRender m_crosshairImage;


		public:
			/** コンストラクタ */
			Crosshair();
			/** デストラクタ */
			~Crosshair();		


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;
		};
	}
}


