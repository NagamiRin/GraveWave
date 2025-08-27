#pragma once
#include "ICharacter.h"

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

class IEnemy :public ICharacter
{
public:

	/// <summary>
	/// コンストラクタ。
	/// </summary>
	IEnemy();

	/// <summary>
	/// デストラクタ。
	/// </summary>
	~IEnemy();

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

public:

	/// <summary>
	/// ダメージを与える処理。
	/// </summary>
	/// <param name="damage">受けるダメージ量</param>
	inline void ApplyDamage(const int damage) 
	{
		m_hp -= damage;
	};

private:

	/// <summary>
	/// 体力。全損すると死亡。
	/// </summary>
	int m_hp = 0;

	/// <summary>
	/// 現在の行動状態。
	/// </summary>
	int m_currentState = 0;
};

