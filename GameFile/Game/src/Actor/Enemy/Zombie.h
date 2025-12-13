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


			public:
				enum EnAnimationVar {
					EnAnimationVar_Attack,
					EnAnimationVar_Death,
					EnAnimationVar_GetUp,
					EnAnimationVar_Hit,
					EnAnimationVar_Idle,
					EnAnimationVar_Walk,
					EnAnimationVar_Max,
				};


			private:
				/** アニメションクリップの種類 */
				std::array<AnimationClip, EnAnimationVar_Max> m_animationClipList;
				/** LODモデル */
				nsCore::ModelLOD* m_modelLOD = nullptr;


				/** プールに戻すフラグ */
				bool m_canRestore = false;


			public:
				/** コンストラクタ */
				Zombie();
				/** デストラクタ */
				~Zombie();


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
				inline ZombieStatus* GetStatus() { return dynamic_cast<ZombieStatus*>(m_status); }

				/** HPを減らす */
				inline void ReduceHP(uint16_t reduceAmount)
				{
					uint16_t  currentHP = GetStatus()->GetHP();
					uint16_t afterHP = currentHP >= reduceAmount ?  currentHP - reduceAmount : 0;
					GetStatus()->SetHP(afterHP);
				}


				nsCore::ModelLOD* GetModel();
				/** プールに戻すフラグを取得 */
				inline bool CanRestore() const { return m_canRestore; }
				/** プールに戻すフラグを設定 */
				inline void SetRestore(const bool restore) { m_canRestore = restore; }
			};
		}
	}
}


