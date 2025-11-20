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
		class NumberUI;


		class RemainingBulletsUI :public IGameObject
		{
		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 文字UI */
			NumberUI* m_ammoUI = nullptr;

			uint8_t m_remainingAmmo = 0;
			uint8_t m_maxAmmo = 0;


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
			inline void SetAmmo(const uint8_t ammo) { m_remainingAmmo = ammo; }
			/** 最大弾数を取得 */
			inline void SetMaxAmmo(const uint8_t ammo) { m_maxAmmo = ammo; }
		};
	}
}