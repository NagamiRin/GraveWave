/**
 * StateMachine.h
 *
 * 状態遷移を行うステートマシンの基底クラス
 */
#pragma once


namespace nsApp
{
	namespace nsActor
	{
		class IState;


		/**
		 * ステートマシンクラス
		 */
		class StateMachine
		{
		protected:
			uint32_t m_requestStateId;
			uint32_t m_currentStateId;
			std::map<uint32_t, IState*> m_stateMap;
			IState* m_currentState = nullptr;


		public:
			/** コンストラクタ */
			StateMachine();
			/** デストラクタ */
			virtual ~StateMachine();

			/** 更新処理 */
			virtual void Update();


		public:
			inline void RequestState(const uint32_t requestStateId)
			{
				m_requestStateId = requestStateId;
			}


		public:
			IState* FindState(const uint32_t stateId)
			{
				auto it = m_stateMap.find(stateId);
				if (it != m_stateMap.end())
				{
					return it->second;
				}
				return nullptr;
			}
		};
	}
}


