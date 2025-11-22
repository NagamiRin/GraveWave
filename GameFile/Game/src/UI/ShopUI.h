/**
 * ShopUI.h
 *
 * ショップUIの描画
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;
		class StringUI;

		/** 
		 * ショップのUIを表示するクラス 
		 */
		class ShopUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;
			/**	各アイテム欄の背景のリスト */
			ImageUI* m_back = nullptr;			
			/** アイコンの背景画像のリスト */
			std::vector<ImageUI*> m_uiItemList;
			/** 今ショップ画面を開いているか */
			bool m_isOpen = false;
			/** 現在のインデックス */
			int8_t m_index = 0;

		public:
			ShopUI();
			~ShopUI();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;		


		public:
			/** インデックスを設定 */
			void SetIndex(int8_t index) { m_index = index; }
		};
	}
}


