#include "stdafx.h"
#include "CollisionManager.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Core/BattleManager.h"


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
	m_collisionPairList.clear();

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

	m_collisionPairList.clear();
}


void CollisionHitManager::DeleteCollisionObject(IGameObject* object)
{
	CollisionObject* targetCollision = nullptr;
	for(auto it = m_collisionInfoList.begin(); it != m_collisionInfoList.end(); ++it)
	{
		if(it->m_object == object)
		{
			targetCollision = it->m_collision;
			m_collisionInfoList.erase(it);
			break;
		}
	}
	if (targetCollision) {
		delete targetCollision;
		targetCollision = nullptr;
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
	nsApp::nsActor::nsBullet::NormalBullet* normalBullet = GetTargetObject<nsApp::nsActor::nsBullet::NormalBullet>(pair, nsApp::nsActor::nsBullet::NormalBullet::ID());
	nsApp::nsActor::nsEnemy::Zombie* zombie = GetTargetObject<nsApp::nsActor::nsEnemy::Zombie>(pair, nsApp::nsActor::nsEnemy::Zombie::ID());

	if (normalBullet == nullptr) {
		return false;
	}
	if (zombie == nullptr) {
		return false;
	}
	
	DeleteGO(normalBullet);
	//ゾンビのHPを減らす
	zombie->ReduceHP(20);
	//死んだなら削除要請
	if (zombie->GetZombieStatus()->GetHP() <= 0) {
		nsApp::nsCore::BattleManager::GetInstance()->DeleteZombie(zombie);
	}

	return true;
}

