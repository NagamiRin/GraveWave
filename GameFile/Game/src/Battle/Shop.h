/**
 * Shop.h
 *
 * ショップクラス
 */
#pragma once


namespace nsApp
{
	namespace nsBattle
	{		
		/**
		 * ショップクラス
		 */
		class Shop
		{
		private:
			/** メニューでのアイテムごとのインデックス */
			int8_t m_menuIndex = 0;
			/** メニューのアイコンを改行するインデックス */
			int8_t m_menuIndexLineBreak = 0;
			/** インデックスの最大値 */
			int8_t m_menuIndexMax = 0;


		public:
			Shop();
			~Shop();
		
		public:
			/** 更新処理 */
			void Update();	
			/** ショップのメニュー操作 */
			void OperateMenu();
			/** 武器の変更をリクエスト */
			void RequestChangeWeapon(uint32_t weaponID);


		public:
			/** 現在のインデックスを取得 */
			inline int8_t GetMenuIndex() const { return m_menuIndex; }


		private:
			/** 自身のインスタンス */
			static Shop* m_instance;


		public:
			/** インスタンスを生成 */
			static void CreateInstance()
			{
				if (!m_instance) m_instance = new Shop();
			}

			/** インスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance) delete m_instance;
			}

			/** インスタンスを取得 */
			static Shop& GetInstance()
			{
				if (m_instance) return *m_instance;
			}
		};
	}
}


