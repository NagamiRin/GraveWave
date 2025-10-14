/**
 * EnemyBase.h
 * 
 * エネミーの基底クラス
 */
#pragma once
#include "src/Actor/CharacterBase.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/** エネミーの行動状態の種類。 */
			enum EnEnemyActionVar {
				enStandby,		//スタンバイ。フィールド上に出現していない状態。
				enProgress,		//進行。
				enAttack,		//攻撃。
				enHit,			//被弾。
				enDead,			//死亡。
			};


			class EnemyBase :public CharacterBase
			{
			protected:
				/** 現在の行動状態。 */
				int m_currentState = 0;

				CollisionObject* m_collisionObject = nullptr;


			public:
				/** コンストラクタ */
				EnemyBase();
				/** デストラクタ */
				virtual ~EnemyBase();


			public:
				/** 生成時に一度だけ呼ばれる関数。 */
				virtual bool Start()override;
				/** 毎フレーム呼ばれる更新処理。 */
				virtual void Update()override;
				/** 描画処理。 */
				virtual void Render(RenderContext& rc)override;
			};
		}
	}
}