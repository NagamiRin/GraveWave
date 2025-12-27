#include "stdafx.h"
#include "system/system.h"

#include<InitGUID.h>
#include<dxgidebug.h>

#include "src/Core/Game.h"
#include "src/Core/ParameterManager.h"
#include "src/Core/SaveData.h"
#include "src/Scene/SceneManager.h"
#include "src/Sound/SoundManager.h"
#include "src/Effect/EffectManager.h"

void ReportLiveObjects()
{
	IDXGIDebug* pDxgiDebug;

	typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
	HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
	fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

	DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&pDxgiDebug);

	// 出力。
	pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_DETAIL);
}

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, TEXT("Game"));
	//////////////////////////////////////
	// ここから初期化を行うコードを記述する。
	//////////////////////////////////////

	//レイトレーシングをオフ
	g_renderingEngine->DisableRaytracing();
	//トーンマッピングをオフ
	g_renderingEngine->DisableTonemap();
	//アンビエントにIBLテクスチャを使用しない
	g_renderingEngine->DisableIBLTextureForAmbient();

	//パラメーターマネージャーのインスタンスを生成。
	ParameterManager::CreateInstance();
	//セーブデータを生成
	nsApp::nsCore::SaveData::Create();
	//シーンマネージャーのゲームオブジェクトを生成
	NewGO<nsApp::nsScene::SceneManagerObject>(enGameObjectPriority_SceneManager, "SceneManagerObject");
	//サウンドマネージャ-のゲームオブジェクトを生成
	NewGO<nsApp::SoundManagerObject>(enGameObjectPriority_SceneManager, "SoundManagerObject");
	//エフェクトマネージャークラスのインスタンスを生成
	NewGO<EffectManagerObject>(enGameObjectPriority_EffectManager, "EffectManager");
	//Gameクラスのオブジェクトを作成
	NewGO<nsApp::nsCore::Game>(0, "game");


	//////////////////////////////////////
	// 初期化を行うコードを書くのはここまで！！！
	//////////////////////////////////////
	
	// ここからゲームループ。
	while (DispatchWindowMessage())
	{
		//if (g_pad[0]->IsTrigger(enButtonA) ){
		//	g_pad[0]->SetVibration(/*durationSec=*/0.5f, /*normalizedPower=*/1.0f);
		//}
		K2Engine::GetInstance()->Execute();
	}

	K2Engine::DeleteInstance();

	//パラメーターマネージャーのインスタンスを破棄。
	ParameterManager::DestroyInstance();
	//セーブデータを削除
	nsApp::nsCore::SaveData::Delete();

#ifdef _DEBUG
	ReportLiveObjects();
#endif // _DEBUG
	return 0;
}

