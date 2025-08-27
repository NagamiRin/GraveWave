#include "stdafx.h"
#include "IEnemy.h"

/// <summary>
/// コンストラクタ
/// </summary>
IEnemy::IEnemy()
{
}

/// <summary>
/// デストラクタ
/// </summary>
IEnemy::~IEnemy()
{
}

/// <summary>
/// 生成時に一度だけ呼ばれる関数
/// </summary>
/// <returns></returns>
bool IEnemy::Start()
{
	return true;
}

/// <summary>
/// 毎フレーム呼ばれる更新処理
/// </summary>
void IEnemy::Update()
{

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="rc"></param>
void IEnemy::Render(RenderContext& rc)
{

}

void IEnemy::ApplyDamage(int damage)
{
}
