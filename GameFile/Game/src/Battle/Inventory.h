/**
 * Inventory.h
 *
 * インベントリクラス
 */
#pragma once


namespace {
	constexpr uint16_t AMMO_LIMIT = 9999;
	constexpr uint16_t MONEY_LIMIT = 99999;
}


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
			inline void AddMoney(const uint16_t money) { 
				if (m_money + money >= MONEY_LIMIT)	m_money = MONEY_LIMIT;
				else m_money += money; 
			}
			/** 所持金を減らす */
			inline void ReduceMoney(const uint16_t money) { 
				if (m_money >= money) m_money -= money;
				m_money = 0;
			}
			/** 所持金を取得 */
			inline uint16_t GetMoney() { return m_money; }

			/** 弾数を追加 */
			inline void AddAmmo(AmmoValue quantity) {
				if (m_mainWeaponAmmo + quantity >= AMMO_LIMIT) {
					m_mainWeaponAmmo = AMMO_LIMIT;
				}
				else m_mainWeaponAmmo += quantity;				
			}
			/** 弾数を減らす */
			inline void ReduceAmmo(AmmoValue quantity) {
				if (m_mainWeaponAmmo >= quantity) m_mainWeaponAmmo -= quantity;
				else m_mainWeaponAmmo = 0;
			}
			/** 弾数を取得 */
			inline AmmoValue GetSpareAmmo() { return m_mainWeaponAmmo; }			

			
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


