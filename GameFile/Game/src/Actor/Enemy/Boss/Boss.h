/**
 * Boss.h
 *
 * ボスクラス
 */
#pragma once
#include "src/Actor/Enemy/EnemyBase.h"
#include "src/Actor/Enemy/Boss/BossStatus.h"
#include "src/Actor/ActorStatus.h"


namespace nsApp {
	namespace nsCore {
		class ModelLOD;
	}
}

enum EnAnimationVar {
	EnAnimationVar_Idle,
	EnAnimationVar_Walk,
	EnAnimationVar_Throw,
	EnAnimationVar_Hit,
	EnAnimationVar_Death,
	EnAnimationVar_Max,
};

namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class BossStateMachine;
			class BossStatus;
			class ThrowStone;


			/**
			 * ボスクラス
			 */
			class Boss : public EnemyBase
			{
				appGameObject(Boss);

				using SuperClass = EnemyBase;


			private:
				/** アニメションクリップの種類 */
				std::array<AnimationClip, EnAnimationVar_Max> m_animationClipList;
				/** ゾンビのステートマシンのポインタ */
				std::unique_ptr<BossStateMachine> m_stateMachine;
				/** 投石の岩 */
				nsEnemy::ThrowStone* m_throwStone = nullptr;


			public:
				/** コンストラクタ */
				Boss();
				/** デストラクタ */
				~Boss();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				bool Start()override;
				/** 毎フレーム呼び出される関数 */
				void Update()override;
				/** モデルの描画処理を行う関数 */
				void Render(RenderContext& rc)override;


			public:
				/** ゾンビのステータスを再設定 */
				void Initialize(const Vector3& initializePosition);
				/** ゾンビを破棄する（非アクティブ状態に） */
				void Destruction();


			public:
				/** ステータスを取得 */
				inline BossStatus* GetStatus() { return dynamic_cast<BossStatus*>(m_status); }
				/** ボスのHPを減らす */
				inline void ReduceHP(uint16_t reduceAmount)
				{
					uint16_t  currentHP = GetStatus()->GetHP();
					if (currentHP <= reduceAmount) reduceAmount = currentHP;
					uint16_t afterHP = currentHP - reduceAmount;
					GetStatus()->SetHP(afterHP);
				}
				/** 岩を飛ばす */
				void ThrowStone(const Vector3& start, const Vector3& end);
				/** アニメーションを再生 */
				inline void PlayAnimation(const EnAnimationVar var, const float complement = 0.0f) {
					m_model.PlayAnimation(var, complement);
				}
				/** アニメーションを再生中か */
				inline bool IsPlayAnimation() { 
					return m_model.IsPlayingAnimation();
				}
			};
		}
	}
}


