/**
 * Wall.h
 * 
 * 防壁クラス
 */
#pragma once
#include "src/Actor/Actor.h"


namespace nsApp
{
	namespace nsActor
	{
		namespace nsWall
		{
			/** 
			 * 防壁クラス 
			 */
			class Wall : public Actor
			{
				appGameObject(Wall);

				using SuperClass = Actor;	


			private:
				/** 最大耐久度 */
				uint16_t m_maxDurability = 0;
				/** 耐久度 */
				uint16_t m_durability = 0;
				/** 防壁の静的な当たり判定 */
				PhysicsStaticObject* m_wallDetection = nullptr;


			public:
				Wall();
				~Wall();


			public:
				virtual bool Start()override;
				virtual void Update()override;
				virtual void Render(RenderContext& rc)override;


			public:
				/** 防壁の耐久度の最大値を取得 */
				inline uint16_t GetMaxDurability()const { return m_maxDurability; }
				/** 防壁の耐久度を取得 */
				inline uint16_t GetDurability()const { return m_durability; }
				/** 防壁の耐久度を減らす */
				inline void ReduceDurability(const uint16_t reduce) {
					if (reduce >= m_durability) m_durability = 0;
					else m_durability -= reduce;
				}
				/** 防壁が壊れたかチェック */
				inline bool CheckDestroyWall()const {
					if (m_durability == 0)return true;
					else return false;
				}
			};
		}		
	}
}