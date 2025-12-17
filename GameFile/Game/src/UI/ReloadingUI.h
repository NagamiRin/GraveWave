/**
 * ReloadingUI.h
 *
 * リロード時間UIの描画
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp{
	namespace nsUI{
		class UICanvas;
		class ImageUI;


		class ReloadingUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** バーの画像 */
			ImageUI* m_bar = nullptr;
			/** リロードの文字 */
			ImageUI* m_string = nullptr;
			/** リロード時間 */
			float m_reloadTime = 0.0f;
			/** 現在の経過時間 */
			float m_currentTime = 0.0f;
			/** 現在の点滅の経過時間 */
			float m_currentBlinkTime = 0.0f;
			

		public:
			ReloadingUI();
			~ReloadingUI();


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;		


		public:
			/** リロード時間を設定 */
			inline void SetReloadTime(const float time) { m_reloadTime = time; }
			/** 現在のリロード時間を設定 */
			inline void SetCurrentReloadTime(const float time) { m_currentTime = time; }
		};
	}
}


