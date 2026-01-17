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
			/** メニューを開いているか */
			bool m_isOpenMenu = false;
			/** 商品の価格 */
			std::map<EnProductType, uint16_t> m_priceVar;
			/** 商品番号 */
			std::map<int8_t, EnProductType> m_productVar;


		public:
			Shop();
			~Shop();
		
		public:
			/** 更新処理 */
			void Update();	
			/** ショップのメニュー操作 */
			void OperateMenu();
			/** 商品の購入 */
			void BuyProducts();
			/** 銃購入の共通処理 */
			void BuyGuns(const uint32_t gunID);
			/** 武器の変更をリクエスト */
			void RequestChangeWeapon(uint32_t weaponID);


		public:
			/** 現在のインデックスを取得 */
			inline int8_t GetMenuIndex() const { return m_menuIndex; }
			/** メニュー開閉の状態を取得 */
			inline bool IsOpenMenu() const { return m_isOpenMenu; }


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


