/**
 * GameCamera.h
 *
 * ゲームカメラクラス
 */
#pragma once


namespace nsApp
{
	namespace nsCamera
	{
		class ActorStatus;
		class Player;

		/**
		 *ゲームオブジェクトの基底クラス
		 */
		class GameCamera : public IGameObject
		{
		private:
			/** カメラ注視点を設定 */
			void SetCameraTarget();
			/** カメラ更新 */
			void CameraUpdate();


		private:
			/** カメラ座標 */
			Vector3 m_cameraPos = Vector3::Zero;
			/** 注視点 */
			Vector3 m_targetPos = Vector3::Zero;
			/** カメラの向き */
			Vector3 m_cameraDir = Vector3::Zero;


		private:
			/** 近平面 */
			float m_cameraNear = 0.0f;
			/** 遠平面 */
			float m_cameraFar = 0.0f;
			/** カメラ座標の初期値 */
			float m_initialCameraPositionX = 0.0f;
			float m_initialCameraPositionY = 0.0f;
			float m_initialCameraPositionZ = 0.0f;
			/** 注視点の初期値 */
			float m_initialTargetPositionX = 0.0f;
			float m_initialTargetPositionY = 0.0f;
			float m_initialTargetPositionZ = 0.0f;
			/** 垂直方向のカメラ画角限界値 */
			float m_verticalLimitAngle = 0.0f;
			/** 水平方向のカメラが書く限界値 */
			float m_horizontalLimitAngle = 0.0f;
			/** カメラ感度 */
			float m_cameraSensitivity = 0.0f;


		public:
			/**
			 * コンストラクタ
			 *
			 * playerのポインタを受け取る
			 */
			GameCamera();
			/** デストラクタ */
			virtual ~GameCamera();


		public:
			/** オブジェクト生成時に一度だけ実行される関数 */
			bool Start()override;
			/** 毎フレーム呼び出される関数 */
			void Update()override;
			/** モデルの描画処理を行う関数 */
			void Render(RenderContext& rc)override;


		public:
			/** カメラ座標を設定 */
			const void SetCameraPos(const Vector3& pos) { m_cameraPos = pos; };
			/** カメラ注視点を設定 */
			const void SetTargetPos(const Vector3& pos) { m_targetPos = pos; };
			/** カメラの向きを設定 */
			const void SetCameraDir(const Vector3& dir) { m_cameraDir = dir; };
		};
	}
}


