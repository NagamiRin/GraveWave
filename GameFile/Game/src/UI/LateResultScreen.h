/**
 * LateResultScreen.h
 *
 * 2つめのリザルト画面の表示
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;


		/** リザルト画面の表示 */
		class LateResultScreen :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			

		public:
			/** コンストラクタ */
			LateResultScreen();
			/** デストラクタ */
			~LateResultScreen();


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


