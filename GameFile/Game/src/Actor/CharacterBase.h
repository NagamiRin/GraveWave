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
		class StateMachine;
		/**
		 * キャラクターの基底クラス
		 */
		class CharacterBase :public Actor
		{
			using SuperClass = Actor;


		protected:
			/** コリジョンの位置 */
			Vector3 m_collisionPosition = Vector3::Zero;
			/** コリジョンオブジェクト */
			CollisionObject* m_collisionObject = nullptr;
			/** ステータスのポインタ */
			ActorStatus* m_status = nullptr;
			/** ステートマシンのポインタ */
			std::unique_ptr<StateMachine> m_stateMachine;


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
		};
	}
}