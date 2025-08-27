#pragma once

class TransForm;
class Actor : public IGameObject
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Actor();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Actor();

public:

	/// <summary>
	/// オブジェクト生成時に一度だけ実行される関数
	/// </summary>
	/// <returns></returns>
	virtual bool Start()override = 0;

	/// <summary>
	/// 毎フレーム呼び出される関数
	/// </summary>
	virtual void Update()override = 0;

	/// <summary>
	/// モデルの描画処理を行う関数
	/// </summary>
	/// <param name="rc"></param>
	virtual void Render(RenderContext& rc)override = 0;

private:


private:

	/// <summary>
	/// モデル描画用変数
	/// </summary>
	ModelRender m_model;
};

