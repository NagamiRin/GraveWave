#include "stdafx.h"
#include "Actor.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Actor::Actor()
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Actor::~Actor()
{
}

/// <summary>
/// �I�u�W�F�N�g�������Ɉ�x�������s�����֐�
/// </summary>
/// <returns></returns>
bool Actor::Start()
{
    m_model.Init("");

    return true;
}

/// <summary>
/// ���t���[���Ăяo�����֐�
/// </summary>
void Actor::Update()
{

}

/// <summary>
/// ���f���̕`�揈�����s���֐�
/// </summary>
/// <param name="rc"></param>
void Actor::Render(RenderContext& rc) 
{
    m_model.Draw(rc);
}