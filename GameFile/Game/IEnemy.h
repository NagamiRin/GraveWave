#pragma once
#include "ICharacter.h"

/// <summary>
/// �G�l�~�[�̍s����Ԃ̎�ށB
/// </summary>
enum EnEnemyActionVar {
	enStandby,		//�X�^���o�C�B�t�B�[���h��ɏo�����Ă��Ȃ���ԁB
	enProgress,		//�i�s�B
	enAttack,		//�U���B
	enHit,			//��e�B
	enDead,			//���S�B
};

class IEnemy :public ICharacter
{
public:

	/// <summary>
	/// �R���X�g���N�^�B
	/// </summary>
	IEnemy();

	/// <summary>
	/// �f�X�g���N�^�B
	/// </summary>
	~IEnemy();

public:

	/// <summary>
	/// �������Ɉ�x�����Ă΂��֐��B
	/// </summary>
	/// <returns></returns>
	bool Start()override;

	/// <summary>
	/// ���t���[���Ă΂��X�V�����B
	/// </summary>
	void Update()override;

	/// <summary>
	/// �`�揈���B
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc)override;

public:

	/// <summary>
	/// �_���[�W��^���鏈���B
	/// </summary>
	/// <param name="damage">�󂯂�_���[�W��</param>
	inline void ApplyDamage(const int damage) 
	{
		m_hp -= damage;
	};

private:

	/// <summary>
	/// �̗́B�S������Ǝ��S�B
	/// </summary>
	int m_hp = 0;

	/// <summary>
	/// ���݂̍s����ԁB
	/// </summary>
	int m_currentState = 0;
};

