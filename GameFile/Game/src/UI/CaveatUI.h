///**
// * CaveatUI.h
// *
// * 警告表示UIの描画
// */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp{
	namespace nsUI{
		class UICanvas;
		class ImageUI;

		class CaveatUI :public IGameObject
		{
			/** ミニマップに表示するエネミーの情報(1体の情報) */
			struct CaveatInformation
			{
				uint64_t m_caveatId;				// iconのID(ユニーク。一意なID)
				uint32_t m_id;						// エネミーの種類
				Vector3 m_position;					// エネミーの座標
				ImageUI* m_icon = nullptr;			// 画像
				bool isUpdate = 0;					// 情報が更新されているか
			};

		private:
			/** キャンバス */
			std::unique_ptr<UICanvas> m_uiCanvas;
			/** 警告アイコンのリスト */
			std::vector<CaveatInformation> m_caveats;
			/** 警告を表示するZ座標 */
			float m_drawCaveatPos = 0.0f;
			

		public:
			CaveatUI();
			~CaveatUI();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;


		public:
			/** エネミーの情報を更新 */
			void UpdateCaveatInformation(const uint64_t iconId, const uint32_t id, const Vector3& position);


		private:
			/** 警告アイコンの位置を計算 */
			Vector3 CalcCaveatPos(CaveatInformation& info);

			CaveatInformation* FindInformation(const uint64_t iconId)
			{
				for (auto& info : m_caveats) {
					if (info.m_caveatId == iconId) {
						return &info;
					}
				}
				return nullptr;
			}
		};
	}
}


