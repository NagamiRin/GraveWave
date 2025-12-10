/**
 * BreakStone.h
 *
 * 岩の破壊表現を行うクラス
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
			class BreakStone : public CharacterBase
			{
				appGameObject(BreakStone);
				using SuperClass = Actor;
				

			private:				
				/** 飛翔の高さ */
				float m_altitude = 0.0f;
				/** 着地までの時間 */
				float m_landingTime = 0.0f;
				/** 回転速度 */
				float m_rotSpeed = 0.0f;
				/** 岩の移動量 */
				Vector3 m_velocity = Vector3::Zero;


			public:
				/** コンストラクタ */
				BreakStone();
				/** デストラクタ */
				~BreakStone();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				bool Start()override;
				/** 毎フレーム呼び出される関数 */
				void Update()override;
				/** モデルの描画処理を行う関数 */
				void Render(RenderContext& rc)override;


				/** ランダムな値を返す */
				uint32_t GetRand();
				/** 岩の初速を求める */
				Vector3& GetForce();
			};
		}
	}
}


