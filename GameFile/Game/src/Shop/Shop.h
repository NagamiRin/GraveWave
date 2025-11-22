/**
 * Shop.h
 *
 * ショップクラス
 */
#pragma once


namespace nsApp
{
	namespace nsShop
	{		
		/**
		 * ショップクラス
		 */
		class Shop
		{
		public:
			Shop();
			~Shop();
		
		public:
			/** 更新処理 */
			void Update();	


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


