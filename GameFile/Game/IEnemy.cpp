#include "stdafx.h"
#include "IEnemy.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
IEnemy::IEnemy()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IEnemy::~IEnemy()
{
}

/// <summary>
/// �������Ɉ�x�����Ă΂��֐�
/// </summary>
/// <returns></returns>
bool IEnemy::Start()
{
	return true;
}

/// <summary>
/// ���t���[���Ă΂��X�V����
/// </summary>
void IEnemy::Update()
{

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="rc"></param>
void IEnemy::Render(RenderContext& rc)
{

}

void IEnemy::ApplyDamage(int damage)
{
}
