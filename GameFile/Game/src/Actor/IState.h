/**
 * IState.h
 * 
 * 各ステート処理の基底クラス
 */
#pragma once


/**
 * StateクラスのIDを定義するマクロ
 * ※必ずクラス内で記載すること
 */
#define appState(name)	\
public:\
	static constexpr uint32_t ID() { return appHash32(#name); }


namespace nsApp
{
	namespace nsActor
	{
		class StateMachine;
		class IStatus;


		/**
		 * ステートパターンとして使用する基底クラス
		 */
		class IState
		{
		protected:
			/** 情報を保持しているオーナー(ステートマシン)のポインタ */
			StateMachine* m_owner;


		public:
			/**
			 * コンストラクタ
			 *
			 * ステートマシンのポインタを渡す
			 */
			IState(StateMachine* owner) : m_owner(owner) {}
			virtual ~IState() {}


			/** 当該の状態に切り替わった時に一度だけ呼ばれる */
			virtual void Enter() = 0;
			/** 更新処理 */
			virtual void Update() = 0;
			/** 他の状態に切り替わる時に一度だけ呼ばれる */
			virtual void Exit() = 0;


		protected:
			template <typename T>
			T* GetOwner() { return dynamic_cast<T*>(m_owner); }
		};
	}
}