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
	btCollisionObject* m_target;
	bool m_isHit = false;
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
	/** 弾関連の当たり判定オブジェクトのリスト */
	std::vector<CollisionInfo> m_collisionBulletInfoList;
	/** 当たり判定のペア */
	std::vector<CollisionPair> m_collisionPairList;
	/** 弾がヒットしたか */
	bool m_isHit = false;


private:
	CollisionHitManager();
	~CollisionHitManager();


public:
	void Update();


public:
	/** 判定処理をしたいオブジェクトを登録 */
	void DeleteCollisionObject(IGameObject* object);
	/** ゲームオブジェクトのコリジョンが残っているかを確認 */
	bool CheckCollision(IGameObject* object);

	/** カプセル状のコリジョンを生成 */
	CollisionObject* CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu, const float height);
	/** キューブ状のコリジョンを生成 */
	CollisionObject* CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const float radisu);
	/** メッシュ状のコリジョンを生成 */
	CollisionObject* CreateCollisionObject(const uint32_t id, IGameObject* gameObject, const Vector3& position, const Quaternion& rotation, const Model& model, const Matrix& matrix);


public:
	/** 弾ヒットのフラグを取得 */
	inline bool IsHit() { return m_isHit; }
	/** 弾ヒットのフラグをリセット */
	inline void ResetHit() { m_isHit = false; }
	

private:
	void RegisterCollisionObject(const uint32_t id,IGameObject* gameObject, CollisionObject* collisionObject);	


private:
	/** 弾関連のヒット処理 */
	bool UpdateHitBullet(CollisionPair& pair);
	/** 岩関連のヒット処理 */
	bool UpdateHitStone(CollisionPair& pair);


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


	/** 弾関連の情報取得 */
	std::vector<CollisionInfo*> FindBulletCollisionInfo(const uint32_t id)
	{
		std::vector<CollisionInfo*> ret;
		for (auto& info : m_collisionBulletInfoList) {
			if (info.m_id == id) {
				ret.push_back(&info);
			}
		}
		return ret;
	}
	CollisionInfo* FindBulletCollisionInfo(const btCollisionObject* btCollision)
	{
		for (auto& info : m_collisionBulletInfoList) {
			auto* targetbtCollision = &info.m_collision->GetbtCollisionObject();
			if (btCollision == targetbtCollision) {
				return &info;
			}
		}
		K2_ASSERT(false, "ここに来ることはない");
		return nullptr;
	}


private:
	static CollisionHitManager* m_instance;


public:
	static void Create()
	{
		if (!m_instance) m_instance = new CollisionHitManager();
	}


	static bool IsAvailable()
	{
		return m_instance != nullptr;
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


/** コリジョンマネージャーのゲームオブジェクト */
class CollisionHitManagerObject :public IGameObject
{
private:
	/** ヒットマネージャーを消してよいか */
	bool m_canDelete = false;


public:
	CollisionHitManagerObject();
	~CollisionHitManagerObject();


public:
	bool Start()override { return true; };
	void Update()override {};
	void Render(RenderContext& rc)override {};


public:
	/** マネージャー削除のフラグを設定 */
	inline void SetDelete(const bool isDelete) { m_canDelete = isDelete; }
};