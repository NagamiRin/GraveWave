/**
 * Inventory.h
 *
 * インベントリクラス
 */
#pragma once


namespace nsApp
{
	namespace nsBattle
	{		
		/**
		 * プレイヤーのインベントリクラス
		 */
		class Inventory
		{
		private:
			Inventory();
			~Inventory();


		public:
			/** 更新処理 */
			void Update();

			
		private:
			/** 自身のインスタンス */
			static Inventory* m_instance;


		public:
			/** インスタンスを作成 */
			static void CreateInstance()
			{
				if (!m_instance) m_instance = new Inventory();
			}

			/** インスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance) delete m_instance;
			}

			/** インスタンスを取得 */
			static Inventory& GetInstance()
			{
				if (m_instance) return *m_instance;
			}
		};
	}
}


