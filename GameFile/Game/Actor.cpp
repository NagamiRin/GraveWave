#include "stdafx.h"
#include "Actor.h"

/// <summary>
/// コンストラクタ
/// </summary>
Actor::Actor()
{
}

/// <summary>
/// デストラクタ
/// </summary>
Actor::~Actor()
{
}

/// <summary>
/// オブジェクト生成時に一度だけ実行される関数
/// </summary>
/// <returns></returns>
bool Actor::Start()
{
    m_model.Init("");

    return true;
}

/// <summary>
/// 毎フレーム呼び出される関数
/// </summary>
void Actor::Update()
{

}

/// <summary>
/// モデルの描画処理を行う関数
/// </summary>
/// <param name="rc"></param>
void Actor::Render(RenderContext& rc) 
{
    m_model.Draw(rc);
}