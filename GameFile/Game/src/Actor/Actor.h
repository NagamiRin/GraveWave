/**
 * Actor.h
 *
 * ゲームオブジェクトのベース
 */
#pragma once


namespace nsApp
{
	namespace nsActor
	{
		class ActorStatus;


		/**
		 *ゲームオブジェクトの基底クラス
		 */
		class Actor : public IGameObject
		{
		protected:
			/** モデル描画用変数 */
			ModelRender m_model;
			/** トランスフォーム */
			Transform m_transform;
			/** ステータスのポインタ */
			ActorStatus* m_status = nullptr;


		public:
			/** コンストラクタ */
			Actor();
			/** デストラクタ */
			virtual ~Actor();


		public:
			/** オブジェクト生成時に一度だけ実行される関数 */
			virtual bool Start()override = 0;
			/** 毎フレーム呼び出される関数 */
			virtual void Update()override = 0;
			/** モデルの描画処理を行う関数 */
			virtual void Render(RenderContext& rc)override = 0;

			
		public:
			/** グローバル座標を取得 */
			const Vector3& GetPosition() const { return m_transform.m_position; }
			/** グローバル座標を設定 */
			void SetPosition(const Vector3& position) { m_transform.m_position = position; }
			/** ローカル座標を取得 */
			const Vector3& GetLocalPosition() const { return m_transform.m_localPosition; }
			/** ローカル座標を設定 */
			void SetLocalPosition(const Vector3& localPosition) { m_transform.m_localPosition = localPosition; }
			/** ローカル回転を取得 */
			const Quaternion& GetRotation() const { return m_transform.m_rotation; }
			/** 回転を設定 */
			void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }

			void SetLocalRotation(const Quaternion& rotation) { m_transform.m_localRotation = rotation; }

			/** スケールを取得 */
			const Vector3& GetScale() const { return m_transform.m_scale; }
			/** スケールを設定 */
			void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }
		};
	}
}


