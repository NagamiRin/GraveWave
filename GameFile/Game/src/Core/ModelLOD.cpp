/**
 * ModelLOD.cpp
 *
 * モデルのLOD
 */
#include "stdafx.h"
#include "ModelLOD.h"


namespace nsApp
{
	namespace nsCore
	{
		ModelLOD::ModelLOD()
		{
		}


		ModelLOD::~ModelLOD()
		{
			for (auto* model : m_modelList) {
				delete model;
				model = nullptr;
			}
			m_modelList.clear();
		}


		void ModelLOD::Update()
		{
			SwitchLODModel();

			m_currentModel->SetPosition(m_position);
			m_currentModel->SetRotation(m_rotation);
			m_currentModel->SetScale(m_scale);
			m_currentModel->Update();
		}


		void ModelLOD::Render(RenderContext& rc)
		{
			if (m_currentModel == nullptr) return;
			m_currentModel->Draw(rc);
		}


		void ModelLOD::Initialize(const std::vector<std::string>& modelPathList, const float switchDis, const uint8_t modelNum)
		{
			m_changeDistance = switchDis;
			m_useLODNum = modelNum;
			m_modelList.reserve(modelNum);
			for (int i = 0; i < modelNum; i++) {
				ModelRender* model = new ModelRender();
				model->Init(modelPathList.at(i).c_str());
				m_modelList.push_back(model);
			}
			m_currentModel = m_modelList.front();
		}


		void ModelLOD::SwitchLODModel()
		{
			//todo for test
			if (m_modelIndex != 0) return;
			if ((g_camera3D->GetPosition() - m_position).LengthSq() <= std::powf(m_changeDistance,2.0f)) {
				m_modelIndex++;
				m_currentModel = m_modelList.at(m_modelIndex);
			}
		}


		void ModelLOD::ResetLOD()
		{
			m_modelIndex = 0;
		}
	}
}