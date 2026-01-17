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
			/** ステータスのポインタ */
			ActorStatus* m_status = nullptr;
			/** ステートマシンのポインタ */
			std::unique_ptr<StateMachine> m_stateMachine;


		public:
			CharacterBase();
			virtual ~CharacterBase();


		public:
			virtual bool Start()override;
			virtual void Update()override;
			virtual void Render(RenderContext& rc)override;
		};
	}
}