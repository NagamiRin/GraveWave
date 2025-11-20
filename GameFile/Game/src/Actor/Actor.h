/**
 * Actor.h
 *
 * ゲームオブジェクトのベース
 */
#pragma once

namespace
{
	//float AngleAboutX(Vector3 dirVec3)
	//{
	//	//2次元に移す。
	//	Vector3 dirVec2 = Vector3(dirVec3.x, 0, dirVec3.z);
	//	//基準のベクトル
	//	Vector3 baseVec = Vector3(1, 0, 0);
	//	//内積
	//	float dotVec = dirVec3.Dot(baseVec);

	//	//外積
	//	Vector3 CrossVec1;
	//	CrossVec1.Cross(baseVec, dirVec2);

	//	//内積の値を角度に変換。
	//	float dir = acos(dotVec);

	//	if (CrossVec1.z < 0)dir * -1;

	//	return dir;
	//};

	//float AngleAboutY(Vector3 dirVec3)
	//{
	//	//2次元に移す。
	//	Vector3 dirVec2 = Vector3(dirVec3.x, dirVec3.y, 0);
	//	//基準のベクトル
	//	Vector3 baseVec = Vector3(1, 0, 0);
	//	//内積
	//	float dotVec = dirVec3.Dot(baseVec);

	//	//外積
	//	Vector3 CrossVec1;
	//	CrossVec1.Cross(baseVec, dirVec2);

	//	//内積の値を角度に変換。
	//	float dir = acos(dotVec);

	//	if (CrossVec1.z < 0)dotVec * -1;

	//	return dir;
	//};
}

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
			/** キャラクターの向いている方向を表すベクトル */
			Vector3 m_direction = Vector3::Zero;


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
				Quaternion t;
				t = GetLocalRotation();

				// Y軸回転(横方向)
				t.SetRotationYFromDirectionXZ(m_direction);

				//// X軸回転(縦)
				//Vector3 temp = Vector3::Front;
				//const float shita = temp.Dot(Vector3(0.0f, direction.y, direction.z));
				//const float xRotValue = acosf(shita);
				//K2_LOG("XRotValue: %f \n", Math::RadToDeg(xRotValue));
				//t.AddRotationX(xRotValue);

				SetLocalRotation(t);

				/*float dirX = AngleAboutX(direction);
				float dirY = AngleAboutY(direction);

				Quaternion rotX;
				Quaternion rotY;
				rotX.SetRotationDegX((dirX / 2 * 3.14) * 360);
				rotY.SetRotationDegY((dirY / 2 * 3.14) * 360);

				rotX.Multiply(rotY);
				Quaternion totalRot = rotX;
				SetLocalRotation(totalRot);*/
			};
			/** アクタの方向を取得 */
			inline const Vector3& GetDirection()const { return m_direction; }
		};
	}
}


