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
			/** キャラクターの向いている方向を表すベクトル */
			Vector3 m_direction = Vector3::Zero;
			/** コリジョンの位置 */
			Vector3 m_collisionPosition = Vector3::Zero;
			/** コリジョンオブジェクト */
			CollisionObject* m_collisionObject = nullptr;


		public:
			Actor();
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
			inline const Vector3& GetPosition() const { return m_transform.m_position; }
			/** グローバル座標を設定 */
			inline void SetPosition(const Vector3& position) { m_transform.m_position = position; }
			/** ローカル座標を取得 */
			inline const Vector3& GetLocalPosition() const { return m_transform.m_localPosition; }
			/** ローカル座標を設定 */
			inline void SetLocalPosition(const Vector3& localPosition) { m_transform.m_localPosition = localPosition; }
			/** グローバル回転を取得 */
			inline const Quaternion& GetRotation() const { return m_transform.m_rotation; }
			/** グローバル回転を設定 */
			inline void SetRotation(const Quaternion& rotation) { m_transform.m_rotation = rotation; }
			/** ローカル回転を取得 */
			inline const Quaternion& GetLocalRotation() const { return m_transform.m_localRotation; }
			/** ローカル回転を設定 */
			inline void SetLocalRotation(const Quaternion& rotation) { m_transform.m_localRotation = rotation; }
			/** スケールを取得 */
			inline const Vector3& GetScale() const { return m_transform.m_scale; }
			/** スケールを設定 */
			inline void SetScale(const Vector3& scale) { m_transform.m_scale = scale; }
			/** アクタの方向を設定 */
			virtual void SetDirection(const Vector3& direction) {
				m_direction = direction;
				{
					// 1. 前方ベクトル(Z)の正規化
					Vector3 zAxis = m_direction;
					zAxis.Normalize();

					// 2. 右ベクトル(X)の算出 (Y軸(0,1,0) と Z軸の外積)
					// 注意: 方向が真上や真下に近いと外積がゼロになり計算不能になるため、
					// 実戦ではここで「ZとUpが平行でないか」のチェックを入れるのが安全です。
					Vector3 xAxis = Vector3::Up;
					xAxis.Cross(m_direction);
					xAxis.Normalize();

					//// ベクトルがゼロに近い場合（特異点）の対策
					//if (XMVector3LengthSq(xAxis).m128_f32[0] < 0.0001f)
					//{
					//	// 仕方がないので別の軸を仮の右ベクトルとするなどの処理が必要
					//	xAxis = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
					//}
					//xAxis = XMVector3Normalize(xAxis);

					// 3. 真の上ベクトル(Y)の算出 (Z軸 と X軸の外積)
					// 既に直交しているので正規化は理論上不要だが、誤差対策ですることもある
					Vector3 yAxis = zAxis;
					yAxis.Cross(xAxis);

					// 4. 回転行列の構築
					// DirectXは行優先(Row-Major)か列優先(Column-Major)かによりますが、
					// XMMATRIXは通常、基底ベクトルを行にセットします。
					Matrix rotMatrix = Matrix::Identity;
					memcpy(&rotMatrix.m[0], &xAxis, sizeof(xAxis)); // X軸
					memcpy(&rotMatrix.m[1], &yAxis, sizeof(yAxis)); // Y軸
					memcpy(&rotMatrix.m[2], &zAxis, sizeof(zAxis)); // Z軸

					Quaternion t;
					t.SetRotation(rotMatrix);
					SetLocalRotation(t);
				}

			};
			/** アクタの方向を取得 */
			inline const Vector3& GetDirection()const { return m_direction; }
		};
	}
}


