/**
 * CharacterBase.h
 * 
 * キャラクターのベース
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		/**
		 * キャラクターの基底クラス
		 */
		class CharacterBase :public Actor
		{
		private:
			/** 速度を位置に適応 */
			void ApplySpeed();


		protected:
			/** 移動方向と速度を表すベクトル */
			Vector3 m_speed = Vector3::Zero;
			/** キャラクターの向いている方向を表すベクトル */
			Vector3 m_direction = Vector3::Zero;


		public:
			/** コンストラクタ */
			CharacterBase();
			/** デストラクタ */
			virtual ~CharacterBase();


		public:
			/** 生成時に一度だけ呼ばれる関数 */
			virtual bool Start()override;
			/** 毎フレーム呼ばれる更新処理 */
			virtual void Update()override;
			/** 描画処理 */
			virtual void Render(RenderContext& rc)override;


		public:
			/** キャラクターの移動速度を設定 */
			const void SetSpeed(const Vector3& speed) { m_speed = speed; }
			/** キャラクターの移動速度を取得 */
			const Vector3& GetSpeed()const { return m_speed; }
			/** キャラクターの方向を設定 */
			const void SetDirection(const Vector3& direction) { m_direction = direction; }
			/** キャラクターの方向を取得 */
			const Vector3& GetDirection()const { return m_direction; }
		};
	}
}