/**
 * WallHPUI.h
 *
 * 防壁のHPのUIを表示するクラス
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;


		/**
		 * 防壁のHPのUIを表示するクラス
		 */
		class WallHPUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** HPバーの本体 */
			ImageUI* m_HPBar = nullptr;
			/** 最大耐久度 */
			uint16_t m_maxDurability = 0;
			/** 耐久度 */
			uint16_t m_durability = 0;


		public:
			WallHPUI();
			~WallHPUI();


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;


		public:
			/** 最大耐久度を設定*/
			inline void SetMaxDurability(const uint16_t maxDurability) { m_maxDurability = maxDurability; }
			/** 耐久度を設定 */
			inline void SetDurability(const uint16_t durability) { m_durability = durability; }
		};
	}
}


