/**
 * RecoilSystem.h
 *
 * 銃の反動を処理する
 */

#pragma once

namespace nsApp {

	class RecoilSystem : public Noncopyable
	{
	private:
		/** 現在のブレ */
		Vector2 m_currentRecoil = Vector2::Zero;
		float m_elapsedTime = 0.0f;

	public:
		RecoilSystem();
		~RecoilSystem();


	public:
		void Update();	


	public:
		/** 反動を加算 */
		void AddRecoil();


	public:
		/** 反動の位置を取得 */
		inline Vector2 GetRecoil() const { return m_currentRecoil; }
	};

}