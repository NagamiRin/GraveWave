/**
 * BackGround.cpp
 *
 * 背景オブジェクト
 */
#include "stdafx.h"
#include "src/Actor/BackGround/BackGround.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsBackGround
        {
            BackGround::BackGround()
            {
                m_model.Init("Assets/ModelData/BackGround/BackGroundObject.tkm");
                m_model.SetPosition(Vector3::Zero);
            }


            BackGround::~BackGround()
            {
                delete m_physicsStaticObject;
            }


            bool BackGround::Start()
            {
                m_physicsStaticObject = new PhysicsStaticObject;
                m_physicsStaticObject->CreateFromModel(m_model.GetModel(), m_model.GetModel().GetWorldMatrix());

                return true;
            }


            void BackGround::Update()
            {
            }


            void BackGround::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }
        }
    }
}