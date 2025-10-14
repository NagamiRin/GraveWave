/**
 * GameCamera.h
 *
 * ゲームカメラクラス
 */
#pragma once


namespace nsApp
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


