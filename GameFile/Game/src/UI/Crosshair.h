/**
 * Crosshair.h
 *
 * クロスヘアの描画
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp{
	namespace nsUI{
		class UICanvas;
		class ImageUI;

		class Crosshair:public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;
			/** ヒットエフェクト */
			ImageUI* m_hitEffect = nullptr;
			/** クロスヘア画像 */
			ImageUI* m_crosshairImage = nullptr;
			/** 照準があっているか */
			bool m_isAiming = false;
			/** 弾がヒットしたか */
			bool m_isHit = false;
			/** 弾がヒットしてからの経過時間 */
			float m_currentTime = 0.0f;
			

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


		public:
			/** 照準が合っているかのフラグを設定 */
			inline void SetAiming(const bool aim) { m_isAiming = aim; }
			/** 弾ヒットフラグを設定 */
			inline void SetHit(const bool hit) { m_isHit = hit; }
		};
	}
}


