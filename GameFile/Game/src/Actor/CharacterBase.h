#pragma once
#include "src/Actor/Actor.h"

class CharacterBase :public Actor
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	CharacterBase();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CharacterBase();

public:

	/// <summary>
	/// 生成時に一度だけ呼ばれる関数
	/// </summary>
	/// <returns></returns>
	bool Start()override;

	/// <summary>
	/// 毎フレーム呼ばれる更新処理
	/// </summary>
	void Update()override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc)override;
private:

	/// <summary>
	/// 移動方向と速度を表すベクトル
	/// </summary>
	Vector3 m_speed = Vector3::Zero;

	/// <summary>
	/// キャラクターの向いている方向を表すベクトル
	/// </summary>
	Vector3 m_direction = Vector3::Zero;

};