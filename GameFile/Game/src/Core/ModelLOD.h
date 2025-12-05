/**
 * ModelLOD.h
 * 
 * モデルのLOD
 */
#pragma once


namespace nsApp
{
	namespace nsCore
	{
		/**
		 * LOD=Level of Detail
		 * カメラとの距離に応じて表示する3Dモデルを切り替える
		 * 特に設定なしならModelRenderのように扱える(3D表示)
		 */
		class ModelLOD : public Noncopyable
		{
		private:
			/** LODモデルの配列 */
			std::vector<ModelRender*> m_modelList;	// モデルリスト
			/** 現在のモデルのインデックス */
			uint8_t m_modelIndex = 0;
			/** 現在描画するモデル */
			ModelRender* m_currentModel = nullptr;
			/** LODモデル表示切替距離(カメラとモデルとの距離によって切り替わる) */
			float m_changeDistance = 0.0f;
			/** LODモデルの数 */
			uint8_t m_useLODNum = 1;

			Vector3 m_position = Vector3::Zero;
			Vector3 m_scale = Vector3::One;
			Quaternion m_rotation = Quaternion::Identity;



		public:
			ModelLOD();
			~ModelLOD();

			void Update();
			void Render(RenderContext& rc);


		public:
			void SetPosition(const Vector3& pos) { m_position = pos; }
			void SetRotation(const Quaternion& rot) { m_rotation = rot; }
			void SetScale(const Vector3& sca) { m_scale = sca; }


		public:
			/** モデルを初期化 */
			void Initialize(const std::vector<std::string>& modelPathList, const float switchDis, const uint8_t modelNum = 2);
			/** リスポーン時のリセット処理 */
			void ResetLOD();


		private:
			/** 描画するLODモデルを切り替える */
			void SwitchLODModel();
		};	
	}
}