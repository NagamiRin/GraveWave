/**
 * Zombie.h
 *
 * ゾンビ（通常）クラス
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


			public:
				//アニメーションの種類
				enum EnAnimationVar {
					EnAnimationVar_Attack,		//攻撃
					EnAnimationVar_Death,		//死亡
					EnAnimationVar_GetUp,		//起き上がり
					EnAnimationVar_Hit,			//被弾
					EnAnimationVar_Idle,		//待機
					EnAnimationVar_Walk,		//歩行
					EnAnimationVar_Max,
				};


			private:
				/** アニメションクリップの種類 */
				std::array<AnimationClip, EnAnimationVar_Max> m_animationClipList;
				/** LODモデル */
				nsCore::ModelLOD* m_modelLOD = nullptr;


				/** プールに戻すフラグ */
				bool m_canRestore = false;
				/** うめき声を再生してからの経過時間 */
				float m_groanTime = 0.0f;


			public:
				Zombie();
				~Zombie();


			public:
				bool Start()override;
				void Update()override;
				void Render(RenderContext& rc)override;


			public:
				/** ゾンビのうめき声を一定時間ごとに再生 */
				void PlayGroan();
				/** ゾンビのステータスを再設定 */
				void Initialize(const Vector3& initializePosition);
				/** ゾンビを破棄する（非アクティブ状態に） */
				void Destruction();
				

			public:
				/** ステータスを取得 */
				inline ZombieStatus* GetStatus() { return dynamic_cast<ZombieStatus*>(m_status); }

				/** HPを減らす */
				inline void ReduceHP(uint16_t reduceAmount)
				{
					uint16_t  currentHP = GetStatus()->GetHP();
					//0以下にさせない
					uint16_t afterHP = currentHP >= reduceAmount ?  currentHP - reduceAmount : 0;
					GetStatus()->SetHP(afterHP);
				}
				//モデルを取得
				nsCore::ModelLOD* GetModel();
				/** プールに戻すフラグを取得 */
				inline bool CanRestore() const { return m_canRestore; }
				/** プールに戻すフラグを設定 */
				inline void SetRestore(const bool restore) { m_canRestore = restore; }
			};
		}
	}
}


