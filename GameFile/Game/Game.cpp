#include "stdafx.h"
#include "Game.h"
#include "src/Actor/Player/Player.h"


bool Game::Start()
{	
	// @todo for test
	NewGO<nsApp::nsActor::nsPlayer::Player>(0);

	return true;
}

void Game::Update()
{
	// g_renderingEngine->DisableRaytracing();
}

void Game::Render(RenderContext& rc)
{
}