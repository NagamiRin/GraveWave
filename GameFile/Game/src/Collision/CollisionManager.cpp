#include "stdafx.h"
#include "CollisionManager.h"
#include "src/Actor/BackGround/BackGround.h"
#include "src/Actor/Bullet/BulletManager.h"
#include "src/Actor/Bullet/NormalBullet.h"
#include "src/Actor/Enemy/Zombie.h"
#include "src/Actor/Enemy/ZombieStatus.h"
#include "src/Actor/Enemy/Boss/Boss.h"
#include "src/Actor/Enemy/Boss/ThrowStone.h"
#include "src/Actor/Enemy/EnemyBase.h"
#include "src/Actor/Wall/Wall.h"
#include "src/Core/BattleManager.h"
#include "src/GameFlow/BattleFlow.h"
#include "src/GameFlow/ScoreCounter.h"


namespace
{
	/** 弾用のSweepTestコールバック */
	struct BulletCallback : public btCollisionWorld::ConvexResultCallback
	{
		bool isHit = false;
		CollisionObject* m_me = nullptr;
		//btCollisionObject* m_me = nullptr;
		const btCollisionObject* m_you = nullptr;

		btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) override
		{
			//自分自身を弾く
			//if (&m_me->GetbtCollisionObject() == convexResult.m_hitCollisionObject) return 0.0f;

			//エネミー以外かつゴーストオブジェクトではない時
			const int collisionAttr = convexResult.m_hitCollisionObject->getUserIndex();
			if ((collisionAttr != nsApp::enCollision_Enemy
				&& collisionAttr != nsApp::enCollision_Stone)
				|| convexResult.m_hitCollisionObject->getInternalType() != btCollisionObject::CO_GHOST_OBJECT) {
				return convexResult.m_hitFraction;
			}

			if (!isHit) {
				isHit = true;
				m_you = convexResult.m_hitCollisionObject;
			}

			return convexResult.m_hitFraction;
		}
	};
}


CollisionHitManager* CollisionHitManager::m_instance = nullptr;


CollisionHitManager::CollisionHitManager()
{
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


CollisionHitManager::~CollisionHitManager()
{
	// コリジョンオブジェクトを削除する
	for (auto& info : m_collisionInfoList) {
		if (info.m_collision) {
			delete info.m_collision;
		}
	}
	m_collisionInfoList.clear();
	m_collisionPairList.clear();
}


void CollisionHitManager::Update()
{
	if (m_isHit)
	{
		m_isHit = false;
	}

	m_collisionPairList.clear();

	// 別処理でペアをつくる
	{
		// 弾
		{
			auto bulletInfoList = FindCollisionInfo(nsApp::nsActor::nsBullet::NormalBullet::ID());

			for (auto* bulletInfo : bulletInfoList) {
				auto* bullet = dynamic_cast<nsApp::nsActor::nsBullet::NormalBullet*>(bulletInfo->m_object);
				// Sweepテストで衝突判定をする
				Vector3 start = bullet->GetLocalPosition();
				Vector3 end = start + (bullet->GetFlyDirection() * bullet->GetBulletSpeed());
				auto* btCollision = &bulletInfo->m_collision->GetbtCollisionObject();
				auto* collisionShape = btCollision->getCollisionShape();
				BulletCallback cb;
				PhysicsWorld::GetInstance()->ConvexSweepTest(collisionShape, start, end, cb);
				if (cb.isHit) {
					auto* targetInfo = FindCollisionInfo(cb.m_you);
					if (targetInfo) {
						m_collisionPairList.push_back(CollisionPair(bulletInfo, targetInfo));
					}
				}
			}
		}
	}

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
		//岩の処理
		if (UpdateHitStone(pair)) {
			continue;
		}
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


bool CollisionHitManager::CheckCollision(IGameObject* object)
{
	CollisionObject* targetCollision = nullptr;
	for (auto it = m_collisionInfoList.begin(); it != m_collisionInfoList.end(); ++it)
	{
		if (it->m_object == object)
		{
			targetCollision = it->m_collision;
			return true;
			break;
		}
	}

	return false;
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


CollisionObject* CollisionHitManager::CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation ,const Model& model,const Matrix& matrix)
{
	CollisionObject* collisionObject = new CollisionObject();
	collisionObject->CreateMesh(position, rotation, model, matrix);

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
	nsApp::nsActor::nsEnemy::Boss* boss = GetTargetObject<nsApp::nsActor::nsEnemy::Boss>(pair, nsApp::nsActor::nsEnemy::Boss::ID());
	nsApp::nsActor::nsEnemy::ThrowStone* throwStone = GetTargetObject< nsApp::nsActor::nsEnemy::ThrowStone>(pair, nsApp::nsActor::nsEnemy::ThrowStone::ID());


	if (!normalBullet) return false;
	if (!zombie && !boss && !throwStone) return false;

	//弾の削除
	m_isHit = true;
	nsApp::nsActor::nsBullet::BulletManager::GetInstance()->DeleteBullet(normalBullet);

	//ゾンビに当たった場合
	if (zombie) {
		zombie->ReduceHP(normalBullet->GetDamage());
		zombie->SetHit(true);
	}

	//ボスに当たった場合
	if (boss) {
		boss->ReduceHP(normalBullet->GetDamage());
		boss->SetHit(true);
		//死んだなら削除要請
		if (boss->GetStatus()->GetHP() <= 0) {
			nsApp::nsCore::BattleManager::GetInstance()->DeleteBoss();			
		}
	}

	//投石に当たった場合
	if (throwStone) {
		throwStone->ReduceDurability(normalBullet->GetDamage());
	}
	
	return true;
}


bool CollisionHitManager::UpdateHitStone(CollisionPair& pair)
{
	nsApp::nsActor::nsEnemy::ThrowStone* throwStone = GetTargetObject< nsApp::nsActor::nsEnemy::ThrowStone>(pair, nsApp::nsActor::nsEnemy::ThrowStone::ID());
	nsApp::nsActor::nsWall::Wall* wall = GetTargetObject< nsApp::nsActor::nsWall::Wall>(pair, nsApp::nsActor::nsWall::Wall::ID());
	

	if (!throwStone) return false;
	if (!wall) return false;

	throwStone->BreakProcess();

	return true;
}

