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
		public:
			/** コンストラクタ */
			ActorStatus();
			/** デストラクタ */
			~ActorStatus();


		public:
			/** 初期化 */
			virtual void Setup() = 0;
		};
	}
}