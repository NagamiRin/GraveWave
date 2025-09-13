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
			const Vector3& GetPosition() const { return m_transform.m_position; }
			void SetPosition(const Vector3& position) { m_transform.m_position = position; }
			const Quaternion& GetRotation() const { return m_transform.m_rotation; }
			void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }	
			const Vector3& GetScale() const { return m_transform.m_scale; }
			void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }
		};
	}
}


