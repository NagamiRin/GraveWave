#include "stdafx.h"
#include "src/Actor/Characters/CharacterBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
CharacterBase::CharacterBase()
{
}

/// <summary>
/// デストラクタ
/// </summary>
CharacterBase::~CharacterBase()
{
}

/// <summary>
/// 生成時に一度だけ呼ばれる関数
/// </summary>
/// <returns></returns>
bool CharacterBase::Start()
{
	return true;
}

/// <summary>
/// 毎フレーム呼ばれる更新処理
/// </summary>
void CharacterBase::Update()
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="rc"></param>
void CharacterBase::Render(RenderContext& rc)
{

}