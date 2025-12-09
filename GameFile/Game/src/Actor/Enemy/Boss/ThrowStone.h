/**
 * ThrowStone.h
 *
 * ボスが投げる岩クラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/**
			 * ボスが投げる岩クラス
			 */
			class ThrowStone : public CharacterBase
			{
				appGameObject(ThrowStone);

				using SuperClass = Actor;
				

			private:
				/** 投石の開始位置 */
				Vector3 m_startPos = Vector3::Zero;
				/** 投石の目標位置 */
				Vector3 m_endPos = Vector3::Zero;
				/** 投石時の高さ */
				float m_altitude = 0.0f;
				/** 岩投げの現在の経過時間 */
				float m_elapsedTime = 0.0f;
				/** 岩が着地するまでの時間 */
				float m_landingTime = 0.0f;
				/** 回転速度 */
				float m_rotSpeed = 0.0f;
				/** 最大耐久度 */
				uint16_t m_maxDurability = 0;
				/** 現在の耐久度 */
				uint16_t m_durability = 0;
				/** 岩が飛翔中か */
				bool m_isFlying = false;


			public:
				/** コンストラクタ */
				ThrowStone();
				/** デストラクタ */
				~ThrowStone();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				bool Start()override;
				/** 毎フレーム呼び出される関数 */
				void Update()override;
				/** モデルの描画処理を行う関数 */
				void Render(RenderContext& rc)override;


			private:
				/** 
				 * 投石のベクトルを加味した位置を計算 
				 *
				 * NOTO:サインカーブを用いて、ベクトルの計算をする
				 */
				Vector3 CalcStonePos();


			public:
				/** 岩を投げる */
				void SetThrowingInfo(const Vector3& start, const Vector3& end);
				/** 岩の耐久度を減らす */
				inline void ReduceDurability(const uint16_t reduce) { m_durability -= reduce; }
			};
		}
	}
}


