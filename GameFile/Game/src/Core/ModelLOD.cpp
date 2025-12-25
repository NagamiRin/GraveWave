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

			for (auto* animationClips : m_animationClipList) {
				delete[] animationClips->m_animationClips;
				animationClips->m_animationClips = nullptr;

				delete animationClips;
				animationClips = nullptr;
			}
			m_animationClipList.clear();
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


		void ModelLOD::Initialize(const float switchDis, const std::function<ModelRender*(int, AnimationClipInfo*)>& func, uint8_t modelNum)
		{
			m_changeDistance = switchDis;
			m_useLODNum = modelNum;
			m_modelList.reserve(modelNum);
			m_animationClipList.resize(modelNum);
			for (int i = 0; i < modelNum; i++) {
				m_animationClipList[i] = new nsCore::ModelLOD::AnimationClipInfo();
				auto* model = func(i, m_animationClipList[i]);
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
				m_currentModel->PlayAnimation(m_currentAnimationNo, m_interpolateTime);
			}
		}


		void ModelLOD::ResetLOD()
		{
			m_modelIndex = 0;
		}
	}
}