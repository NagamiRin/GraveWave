/**
 * Wall.cpp
 *
 * 防壁クラス
 */
#include "stdafx.h"
#include "Wall.h"
#include "src/Core/ParameterManager.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsWall
		{
			Wall::Wall()
			{
				ParameterManager::Get().LoadParameter<MasterWallParameter>("Assets/Parameter/WallParameter.json", [](const nlohmann::json& j, MasterWallParameter& p)
					{
						p.m_maxDurability = j["MaxDurability"].get<uint16_t>();
					});

				auto* param = ParameterManager::Get().GetParameter<MasterWallParameter>();
				m_maxDurability = param->m_maxDurability;
				m_durability = param->m_maxDurability;
			}


			Wall::~Wall()
			{		
			}


			bool Wall::Start()
			{				
				m_model.Init("Assets/ModelData/Wall/Wall.tkm");
				m_model.SetPosition(Vector3::Zero);

				return true;
			}


			void Wall::Update()
			{
				SuperClass::Update();				
			}


			void Wall::Render(RenderContext& rc)
			{
				m_model.Draw(rc);
			}			
		}
	}
}