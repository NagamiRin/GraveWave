#pragma once
#include "graphics/postEffect/PostEffectComponentBase.h"
namespace nsK2Engine
{
	class Fog : public PostEffectComponentBase
	{
	public:
		virtual void OnInit(
			RenderTarget& mainRenderTarget,
			RenderTarget& zprepassRenderTarget,
			RenderTarget& normalRenderTarget,
			RenderTarget& metallicSmoothRenderTarget,
			RenderTarget& albedoRenderTarget);

		virtual void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget);

	private:
		Sprite m_fogSprite;
	};
}