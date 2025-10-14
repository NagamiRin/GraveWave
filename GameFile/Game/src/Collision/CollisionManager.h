/**
 * CollisionManager.h
 * 当たり判定管理
 */
#pragma once


class Player;
class FoodPlate;




struct CollisionInfo
{
	uint32_t m_id;	// 当たり判定のID(プレイヤーと弾がヒットしたみたいな処理をするために必要。自分がだれかの判断)
	IGameObject* m_object;	// 当たり判定を持つオブジェクトのポインタ
	CollisionObject* m_collision; // 当たり判定オブジェクトのポインタ
	//
	CollisionInfo() : m_id(INVALID_ID), m_object(nullptr), m_collision(nullptr) {}
	CollisionInfo(const uint32_t id, IGameObject* object, CollisionObject* collision) : m_id(id), m_object(object), m_collision(collision) {}
};




struct CollisionPair
{
	CollisionInfo* m_left;	// 当たり判定A
	CollisionInfo* m_right;	// 当たり判定B
	//
	CollisionPair() : m_left(nullptr), m_right(nullptr) {}
	CollisionPair(CollisionInfo* left, CollisionInfo* right) : m_left(left), m_right(right) {}
};




/**
 * 当たり判定処理を一括で行うクラス
 * NOTE:シングルトンでインスタンスを一つにしてアクセスポイントを提供する
 */
class CollisionHitManager
{
private:
	/** 当たり判定オブジェクトのリスト */
	std::vector<CollisionInfo> m_collisionInfoList;
	/** 当たり判定のペア */
	std::vector<CollisionPair> m_collisionPairList;


private:
	CollisionHitManager();
	~CollisionHitManager();


public:
	void Update();


public:
	/** 判定処理をしたいオブジェクトを登録 */
	void UnregisterCollisionObject(IGameObject* object);

	CollisionObject* CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu, const float height);
	CollisionObject* CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu);

private:
	void RegisterCollisionObject(const uint32_t id,IGameObject* gameObject, CollisionObject* collisionObject);


private:
	bool UpdateHitBullet(CollisionPair& pair);


private:
	/**
	 * 指定したクラスを取得する
	 * NOTE: 指定したクラスが存在しない場合はnullptrを返す
	 */
	template <typename T>
	T* GetTargetObject(CollisionPair& pair, const uint32_t id)
	{
		if (pair.m_left->m_id == id)
		{
			return static_cast<T*>(pair.m_left->m_object);
		}
		else if (pair.m_right->m_id == id)
		{
			return static_cast<T*>(pair.m_right->m_object);
		}
		return nullptr;
	}


private:
	static CollisionHitManager* m_instance;


public:
	static void Create()
	{
		if (m_instance == nullptr)
		{
			m_instance = new CollisionHitManager();
		}
	}
	static CollisionHitManager& Get()
	{
		return *m_instance;
	}
	static void Delete()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}
};