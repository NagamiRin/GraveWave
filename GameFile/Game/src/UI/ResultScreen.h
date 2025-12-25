/**
 * ResultScreen.h
 *
 * リザルト画面の表示
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
		class ResultScreen :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 文字 */
			ImageUI* m_string = nullptr;
			/** 現在の点滅時間 */
			float m_currentTime = 0.0f;
			

		public:
			/** コンストラクタ */
			ResultScreen();
			/** デストラクタ */
			~ResultScreen();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;


		public:
			void Initialize(const EnResultType type);
		};
	}
}


