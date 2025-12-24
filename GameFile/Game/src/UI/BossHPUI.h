/**
 * BossHPUI.h
 *
 * ボスのHPのUIを表示するクラス
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;


		/**
		 * ボスのHPのUIを表示するクラス
		 */
		class BossHPUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** HPバーの本体 */
			ImageUI* m_HPBar = nullptr;
			/** HPバーの背景 */
			ImageUI* m_back = nullptr;
			/** 最大HP */
			uint16_t m_maxHP = 0;
			/** HP */
			uint16_t m_HP = 0;
			/** ボスの生存状態 */
			float m_isAlive = false;
			/** ボスの位置 */
			Vector3 m_bossPosition = Vector3::Zero;


		public:
			BossHPUI();
			~BossHPUI();


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;


		public:
			/** 最大HPを設定*/
			inline void SetMaxHP(const uint16_t HP) { m_maxHP = HP; }
			/** HPを設定 */
			inline void SetHP(const uint16_t HP) { m_HP = HP; }
			/** ボスの生存状態を設定 */
			inline void SetAlive(const bool isAlive) { m_isAlive = isAlive; }
			/** ボスの位置を更新 */
			inline void SetBossPosition(const Vector3& pos) { m_bossPosition = pos; }
		};
	}
}


