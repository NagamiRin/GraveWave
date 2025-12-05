/**
 * Zombie.h
 *
 * ゾンビ（雑魚）クラス
 */
#pragma once
#include "src/Actor/Enemy/EnemyBase.h"
#include "src/Actor/Enemy/ZombieStatus.h"


namespace nsApp
{
	namespace nsCore
	{
		class ModelLOD;
	}
}

namespace nsApp
{
	namespace nsActor
	{
		namespace nsEnemy
		{
			class ZombieStateMachine;


			/**
			 *ゾンビクラス
			 */
			class Zombie : public EnemyBase
			{
				appGameObject(Zombie);

				using SuperClass = EnemyBase;


			private:
				enum EnAnimationVar {
					EnAnimationVar_Walk,
					EnAnimationVar_Max,
				};

				/** アニメションクリップの種類 */
				std::array<AnimationClip, EnAnimationVar_Max> m_animationClipList;
				/** ゾンビのステートマシンのポインタ */
				std::unique_ptr<ZombieStateMachine> m_stateMachine;
				/** LODモデル */
				nsCore::ModelLOD* m_modelLOD = nullptr;


			public:
				/** コンストラクタ */
				Zombie();
				/** デストラクタ */
				~Zombie();


			public:
				/** オブジェクト生成時に一度だけ実行される関数 */
				virtual bool Start()override;
				/** 毎フレーム呼び出される関数 */
				virtual void Update()override;
				/** モデルの描画処理を行う関数 */
				virtual void Render(RenderContext& rc)override;


			public:
				/** ゾンビのステータスを再設定 */
				void Initialize(const Vector3& initializePosition);
				/** ゾンビを破棄する（非アクティブ状態に） */
				void Destruction();
				/** HPを減らす */
				inline void ReduceHP(uint16_t reduceAmount)
				{
					uint16_t  currentHP = GetZombieStatus()->GetHP();
					if (currentHP <= reduceAmount) reduceAmount = currentHP;
					uint16_t afterHP = currentHP - reduceAmount;
					GetZombieStatus()->SetHP(afterHP);
				}


			public:
				/** ゾンビのステータスをキャスト */
				inline ZombieStatus* GetZombieStatus() { return dynamic_cast<ZombieStatus*>(m_status); }
				/**  */
			};
		}
	}
}


