/**
 * RecoilSystem.cpp
 * 
 * 銃の反動を処理する
 */
#include "stdafx.h"
#include "RecoilSystem.h"
#include "Transform.h"


namespace {
	constexpr float RECOIL_VERTICAL_IMPULSE = 0.1f;      // 縦の跳ね上がり強度
	constexpr float RECOIL_HORIZONTAL_IMPULSE = 2.0f;      // 横の跳ね上がり強度
	constexpr float RECOVERRY_SPEED = 5.0f;		// 元に戻る速さ
	constexpr float MAX_RECOIL = 10.0f;         // 最大跳ね上がり角度
}


namespace nsApp {

	RecoilSystem::RecoilSystem()
	{
		
	}


	RecoilSystem::~RecoilSystem()
	{

	}


	void RecoilSystem::Update()
	{
		// 2. リカバリー処理（徐々に0に戻す）
		// 線形補間（Lerp）を使ってスムーズに戻す
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		m_elapsedTime = min(m_elapsedTime, RECOVERRY_SPEED);
		float rate = m_elapsedTime / RECOVERRY_SPEED;
		m_currentRecoil = Math::Lerp<Vector2>(rate, m_currentRecoil, Vector2(0.0f, 0.0f));

		// 値が小さくなりすぎたら完全に0にする
		if (m_currentRecoil.x < 0.01f) m_currentRecoil.x = 0.0f;
		if (m_currentRecoil.y < 0.01f) m_currentRecoil.y = 0.0f;
	}


	void RecoilSystem::AddRecoil()
	{
		// 縦方向に跳ね上げを加算
		m_currentRecoil.y += RECOIL_VERTICAL_IMPULSE;

		// 横方向はランダムに少しブレさせる
		//todo 後でそれぞれのシード値に
		float randomYaw = ((rand() % 100) / 100.0f - 0.5f) * 0.5f;
		m_currentRecoil.x += randomYaw;

		// 最大値を超えないように制限
		m_currentRecoil.y = min(m_currentRecoil.y, MAX_RECOIL);

		// 反動を徐々に消す処理を開始
		m_elapsedTime = 0.0f;
	}
}