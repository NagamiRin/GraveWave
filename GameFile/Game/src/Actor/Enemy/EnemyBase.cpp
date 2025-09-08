#include "stdafx.h"
#include "src/Actor/Enemy/EnemyBase.h"

/// <summary>
/// コンストラクタ
/// </summary>
EnemyBase::EnemyBase()
{
}

/// <summary>
/// デストラクタ
/// </summary>
EnemyBase::~EnemyBase()
{
}

/// <summary>
/// 生成時に一度だけ呼ばれる関数
/// </summary>
/// <returns></returns>
bool EnemyBase::Start()
{
	return true;
}

/// <summary>
/// 毎フレーム呼ばれる更新処理
/// </summary>
void EnemyBase::Update()
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="rc"></param>
void EnemyBase::Render(RenderContext& rc)
{

}
