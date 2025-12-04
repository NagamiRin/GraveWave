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
			m_isDrawLOD = true;
		}


		ModelLOD::~ModelLOD()
		{
			for (auto* model : m_LODModels) {
				delete model;
				model = nullptr;
			}
			m_LODModels.clear();
		}


		bool ModelLOD::Start()
		{
			return true;
		}


		void ModelLOD::Update()
		{
			m_currentTime += g_gameTime->GetFrameDeltaTime();
			if (m_currentTime >= m_switchModelTime) m_currentTime = m_switchModelTime;

			SwitchLODModel();

			SuperClass::Update();
		}


		void ModelLOD::Render(RenderContext& rc)
		{
			if (!m_currentLODModel) return;
			if (m_isDrawLOD) {
				m_currentLODModel->Draw(rc);
			}
		}


		void ModelLOD::Initialize(const std::vector<std::string>& modelPathList, const float switchTime, const uint8_t modelNum)
		{
			m_switchModelTime = switchTime;

			m_LODModels.reserve(modelNum);

			for (int i = 0; i < modelNum; i++) {
				ModelRender* model = new ModelRender();
				model->Init(modelPathList.at(i).c_str());
				model->SetScale(Vector3(10.0f, 10.0f, 10.0f));
				m_LODModels.push_back(model);
			}
		}


		void ModelLOD::UpdateInformation(const Vector3 position, const Quaternion rotation)
		{
			m_transform.m_localPosition = position;
			m_transform.m_localRotation = rotation;
		}


		void ModelLOD::SwitchLODModel()
		{
			if (m_currentTime == m_switchModelTime) {
				m_currentModelNum++;
				if (m_currentModelNum >= m_LODModels.size()) m_currentModelNum = 0;
				m_currentLODModel = m_LODModels.at(m_currentModelNum);
				m_currentTime = 0.0f;
			}
		}
	}
}