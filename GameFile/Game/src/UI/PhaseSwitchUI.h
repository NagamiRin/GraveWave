///**
// * PhaseSwitchUI.h
// *
// * フェーズ切り替えのメッセージUI
// */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp{
	namespace nsUI{
		class UICanvas;
		class ImageUI;
		class NumberUI;

		class PhaseSwitchUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** メッセージの背景画像 */
			ImageUI* m_back = nullptr;
			/** メッセージの画像 */
			ImageUI* m_message = nullptr;
			/** 数字 */
			NumberUI* m_number = nullptr;
			/** メッセージを表示する時間 */
			float m_drawTime = 0.0f;
			/** 現在の経過時間 */
			float m_currentTime = 0.0f;
			/** 現在のフェーズ */
			uint8_t m_currentPhase = 0;
			/** 変更後のフェーズ */
			uint8_t m_changePhase = 0;
			/** 現在のウェーブ数 */
			uint8_t m_waveNum = 0;

		public:
			PhaseSwitchUI();
			~PhaseSwitchUI();

			/** 切り替え先のフェーズを設定 */
			inline void ChangePhase(uint8_t phase) { m_changePhase = phase; }
			/** 現在のウェーブ数を設定 */
			inline void SetWaveNum(const uint8_t num) { m_waveNum = num; }


		private:
			bool Start() override;
			void Update() override;
			void Render(RenderContext& rc) override;
		};
	}
}


