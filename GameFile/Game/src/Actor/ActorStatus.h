/**
 * ActorStatus.h
 * 
 * アクターステータス
 */
#pragma once


namespace nsApp
{	
	namespace nsActor
	{
		/**
		 * アクターのステータスクラス
		 * NOTE: 中身は空だが、すべてのステータスクラスの基底となる
		 */
		class ActorStatus
		{
		private:


		public:
			/** コンストラクタ */
			ActorStatus();
			/** デストラクタ */
			~ActorStatus();


			/**
			 * セットアップ
			 * NOTE: 必ず継承先で実装すること
			 */
			virtual void Setup() = 0;
		};
	}
}