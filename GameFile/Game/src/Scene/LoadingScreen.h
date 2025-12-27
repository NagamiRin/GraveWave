/**
 * LoadingScreen.h
 *
 * ロード画面の表示
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsScene
	{
		/** ロード画面の表示 */
		class LoadingScreen :public IGameObject
		{
		private:
			/** ローディング画像 */
			SpriteRender m_loadingImage;
			/** 描画のフラグ */
			bool m_isDraw = false;

		public:
			LoadingScreen();
			~LoadingScreen();


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;


		public:
			/** 描画のフラグを設定 */
			inline void SetDraw(const bool draw) { m_isDraw = draw; }
		};
	}
}


