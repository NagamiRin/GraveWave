/**
 * FogObject.cpp
 *
 * フォグのためのボックスオブジェクト
 */
#include "stdafx.h"
#include "FogObject.h"


namespace nsApp
{
    namespace nsActor
    {
        namespace nsBackGround
        {
            FogObject::FogObject()
            {
                // TODO:あとで確認
                m_model.Init("Assets/ModelData/BackGround/FogObject.tkm");
                m_model.SetPosition(Vector3::Zero);
                m_model.Update();
            }


            FogObject::~FogObject()
            {
            }


            bool FogObject::Start()
            {
                return true;
            }


            void FogObject::Update()
            {
            }


            void FogObject::Render(RenderContext& rc)
            {
                m_model.Draw(rc);
            }
        }
    }
}