#include "stdafx.h"
#include "ICharacter.h"

/// <summary>
/// コンストラクタ
/// </summary>
ICharacter::ICharacter()
{
}

/// <summary>
/// デストラクタ
/// </summary>
ICharacter::~ICharacter()
{
}

/// <summary>
/// 生成時に一度だけ呼ばれる関数
/// </summary>
/// <returns></returns>
bool ICharacter::Start()
{
	return true;
}

/// <summary>
/// 毎フレーム呼ばれる更新処理
/// </summary>
void ICharacter::Update()
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="rc"></param>
void ICharacter::Render(RenderContext& rc)
{

}