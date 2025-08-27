#pragma once
#include "Actor.h"

class ICharacter :public Actor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	ICharacter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ICharacter();

public:

	/// <summary>
	/// �������Ɉ�x�����Ă΂��֐�
	/// </summary>
	/// <returns></returns>
	bool Start()override;

	/// <summary>
	/// ���t���[���Ă΂��X�V����
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc)override;

private:

	/// <summary>
	/// �ړ������Ƒ��x��\���x�N�g��
	/// </summary>
	Vector3 m_speed = Vector3::Zero;

	/// <summary>
	/// �L�����N�^�[�̌����Ă��������\���x�N�g��
	/// </summary>
	Vector3 m_direction = Vector3::Zero;


};
