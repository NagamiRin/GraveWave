/**
 * TitleUIManager.h
 *
 * タイトルシーンのUIを管理
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
		class TitleScreen;
		class PressButtonUI;


		class TitleUIManager
		{
		private:
			/** タイトル画面 */
			TitleScreen* m_titleScreen = nullptr;
			/** PressButtonのUI */
			PressButtonUI* m_pressButton = nullptr;

			std::vector<INotify*> m_notifyList;


		private:
			/** コンストラクタ */
			TitleUIManager();
			/** デストラクタ */
			~TitleUIManager();


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
			static TitleUIManager* m_instance;


		public:
			/** TitleUIManagerのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new TitleUIManager();
				}
			}
			/** TitleUIManagerのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** TitleUIManagerのインスタンスを取得 */
			static TitleUIManager* GetInstance() { return m_instance; }
		};		
	}
}


