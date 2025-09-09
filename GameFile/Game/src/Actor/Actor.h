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
		private:
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
			~Actor();


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
		};
	}
}


