#pragma once

class TransForm;
class Actor : public IGameObject
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Actor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Actor();

public:

	/// <summary>
	/// �I�u�W�F�N�g�������Ɉ�x�������s�����֐�
	/// </summary>
	/// <returns></returns>
	virtual bool Start()override = 0;

	/// <summary>
	/// ���t���[���Ăяo�����֐�
	/// </summary>
	virtual void Update()override = 0;

	/// <summary>
	/// ���f���̕`�揈�����s���֐�
	/// </summary>
	/// <param name="rc"></param>
	virtual void Render(RenderContext& rc)override = 0;

private:


private:

	/// <summary>
	/// ���f���`��p�ϐ�
	/// </summary>
	ModelRender m_model;
};

