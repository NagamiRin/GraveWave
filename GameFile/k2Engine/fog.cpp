#include "k2EnginePreCompile.h"
#include "fog.h"
namespace nsK2Engine {
	void Fog::OnInit(
		RenderTarget& mainRenderTarget,
		RenderTarget& zprepassRenderTarget,
		RenderTarget& normalRenderTarget,
		RenderTarget& metallicSmoothRenderTarget,
		RenderTarget& albedoRenderTarget)
	{
		SpriteInitData spriteInitData;
		spriteInitData.m_fxFilePath = "Assets/shader/postEffect/fog.fx";
		spriteInitData.m_vsEntryPointFunc = "VSMain";
		spriteInitData.m_psEntryPoinFunc = "PSMain";

		spriteInitData.m_width = mainRenderTarget.GetWidth();
		spriteInitData.m_height = mainRenderTarget.GetHeight();
		spriteInitData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();
		spriteInitData.m_textures[1] = &zprepassRenderTarget.GetRenderTargetTexture();

		spriteInitData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();

		m_fogSprite.Init(spriteInitData);
	}

	void Fog::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		g_graphicsEngine->BeginGPUEvent("Fog");

		rc.WaitUntilToPossibleSetRenderTarget(mainRenderTarget);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(mainRenderTarget);
		// 輝度抽出を行う
		m_fogSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(mainRenderTarget);

		g_graphicsEngine->EndGPUEvent();
	}
}