#include "stdafx.h"
#include "CollisionManager.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Actor/Enemy/Zombie.h"


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


CollisionHitManager::CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


CollisionHitManager::~CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


void CollisionHitManager::Update()
{
	// ヒットするオブジェクトのペアを作る
	const uint32_t colSize = static_cast<uint32_t>(m_collisionInfoList.size());
	for (uint32_t i = 0; i < colSize; ++i) {
		for (uint32_t j = i+1; j < colSize; ++j) {
			CollisionInfo* infoA = &m_collisionInfoList[i];
			CollisionInfo* infoB = &m_collisionInfoList[j];

			if(infoA->m_collision->IsHit(infoB->m_collision) || infoB->m_collision->IsHit(infoA->m_collision))
			{
				// CollisionPairの中に同じ組み合わせがないかチェック
				bool exists = false;
				for (const auto& pair : m_collisionPairList) {
					if ((pair.m_left == infoA && pair.m_right == infoB) || (pair.m_left == infoB && pair.m_right == infoA)) {
						exists = true;
						break;
					}
				}
				// すでに登録済みではないなら追加する
				if (!exists) {
					m_collisionPairList.push_back(CollisionPair(infoA, infoB));
				}
			}
		}
	}

	// ヒットしたペアで衝突した時の処理をする
	// 今回のゲームではないがプレイヤーの攻撃がエネミーにあたったのでHPを減らすみたいなことをする
	for (auto& pair : m_collisionPairList) {
		
		// 弾の処理
		if (UpdateHitBullet(pair)) {
			continue;
		}
		// ここでなにかする

		// ここでも何かする
	}
}


void CollisionHitManager::UnregisterCollisionObject(IGameObject* object)
{
	for(auto it = m_collisionInfoList.begin(); it != m_collisionInfoList.end(); ++it)
	{
		if(it->m_object == object)
		{
			m_collisionInfoList.erase(it);
			break;
		}
	}
}


CollisionObject* CollisionHitManager::CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu, const float height)
{
	CollisionObject* collisionObject = new CollisionObject();
	collisionObject->CreateCapsule(position, rotation, radisu, height);

	RegisterCollisionObject(id, gameObject, collisionObject);

	return collisionObject;
}


CollisionObject* CollisionHitManager::CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu)
{
	CollisionObject* collisionObject = new CollisionObject();
	collisionObject->CreateSphere(position, rotation, radisu);

	RegisterCollisionObject(id, gameObject, collisionObject);
	
	return collisionObject;
}

void CollisionHitManager::RegisterCollisionObject(const uint32_t id, IGameObject* gameObject, CollisionObject* collisionObject)
{
	CollisionInfo info(id, gameObject, collisionObject);
	m_collisionInfoList.push_back(std::move(info));
}

bool CollisionHitManager::UpdateHitBullet(CollisionPair& pair)
{
	//// 判定対象が料理スペースだった場合
	//CoockingSpace* cookingSpace = GetTargetObject<CoockingSpace>(pair, enCollisionType_CookingSpace);
	//Player* player = GetTargetObject<Player>(pair, enCollisionType_Player);

	//// 料理スペースじゃないなら処理しない
	//if (cookingSpace == nullptr) {
	//	return false;
	//}
	//// playerじゃないなら処理しない
	//if (player == nullptr) {
	//	return false;
	//}

	//// 料理スペースにプレイヤーが入ったときの処理
	//player->GetStateMachine()->SetInCookingSpace(true);
	//
	return true;
}

