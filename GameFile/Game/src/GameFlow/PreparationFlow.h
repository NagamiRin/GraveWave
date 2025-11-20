/**
 * PreparationFlow.h
 *
 * 準備フェーズの処理
 */
#pragma once


namespace nsApp
{
	namespace nsFlow
	{
		/**
		 * 準備フェーズの処理を行うクラス
		 */
		class PreparationFlow
		{
		private:
			/** カウントダウンを始めるまでの時間 */
			float m_toCountDownTime = 0.0f;
			/** 戦闘フェーズまでのカウントダウン */
			float m_specifiedSeconds = 0.0f;
			/** 現在のカウントダウン */
			float m_currentCount = 0.0f;
			/** カウントダウンを表示させるか */
			bool m_isDrawCount = false;


		private:
			PreparationFlow();
			~PreparationFlow();


		public:
			/** 更新処理 */
			void Update();


		public:
			/** 準備フェーズの情報をセット */
			void SetInformation();
			/** 次のフェーズへ移行する */
			void ChangeNextPhase();


		public:
			/** カウントダウンの秒数を取得 */
			inline float GetSpecifiedSeconds() { return m_specifiedSeconds; }
			/** 現在のカウントダウンを取得 */
			inline float GetCurrentCount() { return m_currentCount; }
			/** カウントダウンを表示させるかのフラグを取得 */
			inline bool IsDrawCount() { return m_isDrawCount; }


		private:
			/** 自身のインスタンス */
			static PreparationFlow* m_instance;


		public:
			/** PreparationFlowクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new PreparationFlow();
				}
			}
			/** PreparationFlowクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** PreparationFlowクラスのインスタンスを取得 */
			static PreparationFlow* GetInstance() { return m_instance; }
		};
	}
}


