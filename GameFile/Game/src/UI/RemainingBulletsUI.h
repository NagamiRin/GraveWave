/**
 * RemainingBulletsUI.h
 *
 * 残弾数UI
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;
		class NumberUI;


		class RemainingBulletsUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 残弾数UI */
			NumberUI* m_ammoUI = nullptr;
			/** 予備弾数UI */
			NumberUI* m_spareAmmoUI = nullptr;
			/** 銃のアイコン */
			ImageUI* m_gunIcon = nullptr;
			/** ∞マーク */
			ImageUI* m_infiniteMark = nullptr;
			/** 残弾数 */
			uint16_t m_remainingAmmo = 0;
			/** 予備弾数 */
			uint16_t m_spareAmmo = 0;
			/** 現在装備している銃の名前 */
			std::string m_gunName;
			/** 切り替えたい銃の名前 */
			std::string m_changeGunName;
			/** 装備中の武器種 */
			EnWeaponType m_equipType = enWeaponType_None;


		public:
			/** コンストラクタ */
			RemainingBulletsUI();
			/** デストラクタ */
			~RemainingBulletsUI();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;


		public:
			/** 現在の弾数を設定 */
			inline void SetAmmo(const uint16_t ammo) { m_remainingAmmo = ammo; }
			/** 予備弾数を設定 */
			inline void SetSpareAmmo(const uint16_t ammo) { m_spareAmmo = ammo; }
			/** 銃の名前を設定 */
			inline void SetGunName(const std::string& name) { m_changeGunName = name; }
			/** 装備中の武器種を設定 */
			inline void SetEquipType(const EnWeaponType type) { m_equipType = type; }
		};
	}
}