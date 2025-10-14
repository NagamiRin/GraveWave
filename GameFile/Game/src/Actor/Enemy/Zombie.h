/**
 * Zombie.h
 *
 * ゾンビ（雑魚）クラス
 */
#pragma once
#include "src/Actor/Enemy/EnemyBase.h"
#include "src/Actor/Enemy/EnemyStatus.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			/**
			 *ゾンビクラス
			 */
			class Zombie : public EnemyBase
			{
				appGameObject(Zombie);


			private:
				enum EnAnimationVar {
					EnAnimationVar_Walk,
					EnAnimationVar_Max,
				};


			private:
				Vector3 m_targetPos = Vector3::Zero;
				/** アニメションクリップの種類 */
				std::array<AnimationClip, EnAnimationVar_Max> m_animationClipList;


			public:
				/** コンストラクタ */
				Zombie();
				/** デストラクタ */
				virtual ~Zombie();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				virtual bool Start()override;
				/** 毎フレーム呼び出される関数 */
				virtual void Update()override;
				/** モデルの描画処理を行う関数 */
				virtual void Render(RenderContext& rc)override;
			};
		}
	}
}


