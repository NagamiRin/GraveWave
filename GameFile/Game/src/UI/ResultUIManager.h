/**
 * ResultUIManager.h
 *
 * リザルトのUIを管理
 */
#pragma once


namespace nsApp
{
	enum EnNotifyType
	{
		enNotifyType_None,
	};


	struct INotify
	{
		EnNotifyType m_notifyType;
		//
		INotify(EnNotifyType type) : m_notifyType(type) {}
	};


	namespace nsUI
	{
		class ResultScreen;


		class ResultUIManager
		{			
		private:
			std::vector<INotify*> m_notifyList;
			/** リザルト画面 */
			ResultScreen* m_resultScreen = nullptr;


		private:
			/** コンストラクタ */
			ResultUIManager();
			/** デストラクタ */
			~ResultUIManager();


		public:
			/** 更新処理 */
			void Update();


		public:
			void AddNotify(INotify* notify)
			{
				m_notifyList.push_back(notify);
			}


		private:
			/** 自身のインスタンス */
			static ResultUIManager* m_instance;


		public:
			/** ResultUIManagerのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new ResultUIManager();
				}
			}
			/** ResultUIManagerのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** ResultUIManagerのインスタンスを取得 */
			static ResultUIManager* GetInstance() { return m_instance; }
		};		
	}
}


