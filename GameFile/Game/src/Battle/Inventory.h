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
			/** 弾数の可変領域 */
			using AmmoValue = uint16_t;
			/** 所持金の可変領域 */	
			using MoneyValue = uint16_t;


		private:
			/** 所持金 */
			MoneyValue m_money = 0;

			/** サブ武器の弾数 */
			AmmoValue m_subWeaponAmmo = 0;
			/** メイン武器の弾数 */
			AmmoValue m_mainWeaponAmmo = 0;

			/** サブ武器のIDのリスト */
			std::vector<uint32_t> m_subWeaponIDList;
			/** メイン武器のIDのリスト */
			std::vector<uint32_t> m_mainWeaponIDList;


		private:
			Inventory();
			~Inventory();


		public:
			/** 更新処理 */
			void Update();


		public:
			/** サブ武器のIDをセット */
			inline void SetSubWeaponID(const uint32_t id) { m_subWeaponIDList.push_back(id); }
			inline const std::vector<uint32_t>& GetSubWeaponID() const { return m_subWeaponIDList; }
			/** メイン武器のIDをセット */
			inline void SetMainWeaponID(const uint32_t id) { m_mainWeaponIDList.push_back(id); }
			inline const std::vector<uint32_t>& GetMainWeaponID() const { return m_mainWeaponIDList; }

			/** 所持金を加算 */
			inline void AddMoney(const uint16_t money) { m_money += money; }
			/** 所持金を取得 */
			inline uint16_t GetMoney() { return m_money; }

			
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


