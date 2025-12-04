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
		class NumberUI;

		/** 
		 * ショップのUIを表示するクラス 
		 */
		class ShopUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;		
			/** アイコンの背景画像のリスト */
			std::vector<ImageUI*> m_uiBackList;			
			/** 商品の値段 */
			std::vector<NumberUI*> m_itemPriceList;
			/** 今ショップ画面を開いているか */
			bool m_isOpen = false;
			/** 変更前のインデックス */
			int8_t m_beforeIndex = 0;
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
			inline void SetIndex(const int8_t index) { m_index = index; }
			/** メニュー開閉の状態を設定 */
			inline void SetIsOpen(const bool open) { m_isOpen = open; }
		};
	}
}


