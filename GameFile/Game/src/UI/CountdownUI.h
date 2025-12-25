/**
 * CountdownUI.h
 *
 * カウントダウンUIの描画
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;
		class NumberUI;

		/** 戦闘フェーズへのカウントダウンメッセージを描画する */
		class CountdownUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;
			/** カウントダウンの秒数 */
			NumberUI* m_count = nullptr;
			/** 時計の背景 */
			ImageUI* m_clock = nullptr;
			/** 時計の針 */
			ImageUI* m_hands = nullptr;
			/** 針の回転用 */
			Quaternion m_handsRot = Quaternion::Identity;

			/** 残りのカウントダウンの秒数 */
			float m_currentSeconds = 0.0f;
			/** カウントダウンの秒数 */
			float m_countTime = 0.0f;
			/** カウントダウンを表示するか */
			bool m_isDrawCount = false;
			/** 点滅を始めてからの経過時間 */
			float m_blinkTime = 0.0f;
			

		public:
			CountdownUI();
			~CountdownUI();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;


		public:
			/** 残りのカウントダウンの秒数を設定 */
			inline void SetCurrentSeconds(const float seconds) { m_currentSeconds = seconds; }
			/** カウントダウンの秒数を設定 */
			inline void SetSpecifiedSeconds(const float seconds) { m_countTime = seconds; }
			/** カウントダウンを表示させるかを設定 */
			inline void SetDrawCount(const bool Draw) { m_isDrawCount = Draw; }
		};
	}
}


