#pragma once
#include "src/Actor/CharacterBase.h"

/// <summary>
/// エネミーの行動状態の種類。
/// </summary>
enum EnEnemyActionVar {
	enStandby,		//スタンバイ。フィールド上に出現していない状態。
	enProgress,		//進行。
	enAttack,		//攻撃。
	enHit,			//被弾。
	enDead,			//死亡。
};

class EnemyBase :public CharacterBase
{
public:

	/// <summary>
	/// コンストラクタ。
	/// </summary>
	EnemyBase();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~EnemyBase();

public:

	/// <summary>
	/// 生成時に一度だけ呼ばれる関数。
	/// </summary>
	/// <returns></returns>
	bool Start()override;

	/// <summary>
	/// 毎フレーム呼ばれる更新処理。
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理。
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc)override;

private:

	/// <summary>
	/// 現在の行動状態。
	/// </summary>
	int m_currentState = 0;
};

