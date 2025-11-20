/**
 * MiniMapUI.h
 *
 * ミニマップUIの表示
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;

		/** ミニマップを表示する */
		class MiniMapUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;
			/** 敵アイコンのリスト */
			std::unique_ptr<ImageUI>m_enemyIconList;
			

		public:
			MiniMapUI();
			~MiniMapUI();


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


