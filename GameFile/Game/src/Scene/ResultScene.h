/**
 * ResultScene.h
 *
 * リザルトシーン
 */
#pragma once
#include "src/Scene/IScene.h"


namespace nsApp
{
	namespace nsUI
	{
		class ResultScreen;
		class LateResultScreen;
	}

	namespace nsScene
	{


		/**
		 * リザルトシーン
		 */
		class ResultScene :public IScene
		{
			enum EnStep {
				enType_Step1,
				enType_Step2,
				enType_Step3,
				enType_None
			};

		public:
			appScene(ResultScene);


		private:
			/** リザルトの画面 */
			nsUI::ResultScreen* m_resultScreen = nullptr;;
			/** リザルトの画面（2つめ） */
			nsUI::LateResultScreen* m_lateResultScreen = nullptr;
			/** リザルトのステップ */
			EnStep m_step;


		public:
			ResultScene();
			~ResultScene();


		public:
			bool Start()override;
			void Update()override;
			bool RequestScene(uint32_t& id)override;
		};
	}
}


