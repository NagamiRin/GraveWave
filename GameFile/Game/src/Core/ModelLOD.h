/**
 * ModelLOD.h
 * 
 * モデルのLOD
 */
#pragma once
#include "src/Actor/Actor.h" 


namespace nsApp
{
	namespace nsCore
	{
		class ModelLOD : public nsActor::Actor
		{
			using SuperClass = Actor;


		private:
			/** LODモデルの配列 */
			std::vector<ModelRender*> m_LODModels;
			/** 現在描画するLODモデル */
			ModelRender* m_currentLODModel;
			/** LODモデルを表示するプレイヤーとの距離 */
			Vector3 m_drawLODDistance = Vector3::Zero;
			/** LODモデルを描画するか */
			bool m_isDrawLOD = false;
			/** 現在のLODモデルの番号 */
			uint8_t m_currentModelNum = 0;
			/** LODモデルを切り替える時間 */
			float m_switchModelTime = 0.0f;
			/** 現在の切り替え時間 */
			float m_currentTime = 0.0f;


		public:
			ModelLOD();
			~ModelLOD();


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;


		public:
			/** モデルを初期化 */
			void Initialize(const std::vector<std::string>& modelPathList, const float switchTime, const uint8_t modelNum = 1);
			/** 情報を更新 */
			void UpdateInformation(const Vector3 position,const Quaternion rotation);

		private:
			/** 描画するLODモデルを切り替える */
			void SwitchLODModel();


		public:
			/** LODを表示するかを設定 */
			inline void SetDrawLOD(const bool isDraw) { m_isDrawLOD = isDraw; }
			/** LODを表示するかを取得 */
			inline bool IsDrawLOD() const { return m_isDrawLOD; }
		};	
	}
}