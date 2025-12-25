/**
 * MiniMapUI.h
 *
 * ミニマップUIの表示
 */
#pragma once
#include "src/UI/UIBase.h"

namespace nsApp
{
	namespace nsUI
	{
		class UICanvas;
		class ImageUI;

		/** ミニマップを表示する */
		class MiniMapUI :public IGameObject
		{
		private:

			/** ミニマップに表示するエネミーの情報(1体の情報) */
			struct EnemyIconInformation
			{
				uint64_t m_iconId;					// iconのID(ユニーク。一意なID)
				uint32_t m_id;						// エネミーの種類
				Vector3 m_position;					// エネミーの座標
				ImageUI* m_icon = nullptr;			// 画像
				bool m_isUpdate = false;					// 情報が更新されているか
			};

			struct BossIconInformation
			{
				bool m_isAlive;
				Vector3 m_position;
				ImageUI* m_icon = nullptr;
			};

		private:
			/** キャンバス */
			std::unique_ptr<UICanvas>m_uiCanvas;
			/** 敵アイコンのリスト */
			std::vector<EnemyIconInformation> m_enemyIcons;
			/** ボス用のアイコン */
			BossIconInformation m_bossIcon;
			/** レーダーの針 */
			ImageUI* m_radar = nullptr;
			/** レーダーの現在の角度 */
			float m_radarRot = 0.0f;
			

		public:
			MiniMapUI();
			~MiniMapUI();


		private:
			/** 初期化処理 */
			bool Start() override;
			/**更新処理*/ 
			void Update() override;
			/** 描画処理 */
			void Render(RenderContext& rc) override;


		public:
			void UpdateIconInformation(const uint64_t iconId, const uint32_t id, const Vector3& position);


		private:
			EnemyIconInformation* FindInformation(const uint64_t iconId)
			{
				for (auto& info : m_enemyIcons) {
					if (info.m_iconId == iconId) {
						return &info;
					}
				}
				return nullptr;
			}


		public:
            /** ボスの生存状態を設定 */  
            inline void SetBossInformation(const bool alive, const Vector3& pos) {  
                m_bossIcon.m_isAlive = alive;  
                m_bossIcon.m_position = pos;  
            }
		};	
	}
}


