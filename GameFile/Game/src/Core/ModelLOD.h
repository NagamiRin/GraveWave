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
		public:
			struct AnimationClipInfo : Noncopyable
			{
				AnimationClip* m_animationClips = nullptr;		// 配列として作成してください
				uint8_t m_animNum;								// アニメーション数
			};

		private:
			/** モデルのリスト */ 
			std::vector<ModelRender*> m_modelList;	
			/** アニメーションクリップのリスト */
			std::vector<AnimationClipInfo*> m_animationClipList;
			/** 現在のアニメーションの番号 */
			int m_currentAnimationNo = 0;
			/** 補完時間 */
			float m_interpolateTime = 0.0f;

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
			void Initialize(const float switchDis, const std::function<ModelRender*(int, AnimationClipInfo*)>& func, uint8_t modelNum = 2);
			/** リスポーン時のリセット処理 */
			void ResetLOD();

			// アニメーション再生
			void PlayAnimation(int animationNo, float interpolateTime = 0.0f)
			{
				m_currentModel->PlayAnimation(animationNo, interpolateTime);
				m_currentAnimationNo = animationNo;
				m_interpolateTime = interpolateTime;
			}


		private:
			/** 描画するLODモデルを切り替える */
			void SwitchLODModel();			


		public:
			/** アニメーション再生中のフラグを返す */
			inline const bool IsPlayAnimation() const {
				if (m_currentModel->IsPlayingAnimation()) return true;
				return false;
			}
		};	
	}
}