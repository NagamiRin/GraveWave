/**
 * PressButtonUI.cpp
 *
 * PressButtonの文字列の表示
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;


		/** PressButtonの文字列 */
		class PressButtonUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** PressEnyButtonの文字 */
			ImageUI* m_string = nullptr;
			/** 現在の時間 */
			float m_currentTime = 0.0f;
			

		public:
			PressButtonUI();
			~PressButtonUI();


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;
		};
	}
}


