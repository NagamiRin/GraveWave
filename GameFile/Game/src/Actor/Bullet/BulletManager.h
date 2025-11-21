/**
 * BulletManager.h
 *
 * 弾管理クラス
 */
#pragma once


namespace nsApp
{
	namespace nsActor
	{
		namespace nsBullet
		{
			class BulletBase;
			class NormalBullet;


			/**
			 * 通常弾クラス
			 */
			class BulletManager
			{
			private:
				/** 通常弾のリスト */
				std::vector<NormalBullet*> m_normalBulletList;


			private:
				BulletManager();
				~BulletManager();


			private:
				/** 初期化 */
				void Setup();


			public:
				/** 更新処理 */
				void Update();


			public:
				/**
				 * 弾を生成
				 * 指定した弾を生成するためテンプレートにしている
				 * (弾は複数種類あるため)
				 */
				template<typename T>
				T* CreatBullet(const Vector3& direction, const Vector3& position, const float speed, uint8_t damage)
				{
					// 弾を生成
					T* bullet = NewGO<T>(0, "Bullet");
					// 管理に追加
					RegisterBullet(bullet);	// 関数のオーバーロードを用いて登録(引数の弾の型によって関数が変わる)
					//パラメーター引き渡し
					bullet->SetParameter(direction, position, speed, damage);
					return bullet;
				}


			private:
				/** 弾登録 */
				template <typename T>
				void RegisterBullet(T* bullet)
				{
					K2_ASSERT(false, "対応していない弾の種類です");
				}
				void RegisterBullet(NormalBullet* bullet)
				{
					m_normalBulletList.push_back(bullet);
				}


				/** 弾削除 */
				template <typename T>
				void DeleteBullet(T* bullet)
				{
					K2_ASSERT(false, "対応していない弾の種類です");
				}
				void DeleteBullet(NormalBullet* bullet)
				{
					auto it = std::find(m_normalBulletList.begin(), m_normalBulletList.end(), bullet);
					if (it != m_normalBulletList.end())
					{
						m_normalBulletList.erase(it);
					}
					delete bullet;
				}

				/** 一定時間経った弾は自動的に削除 */
				void NaturalDelete();



				/**
				 * シングルトン関連
				 */
			private:
				/** 自身のインスタンス */
				static BulletManager* m_instance;


			public:
				/** インスタンスを作成 */
				static void CreateInstance()
				{
					if (!m_instance)m_instance = new BulletManager();					
				}

				/** インスタンスを削除 */
				static void DeleteInstance()
				{
					if (m_instance)
					{
						delete m_instance;
						m_instance = nullptr;
					}
				}

				/** インスタンスを取得 */
				static BulletManager* GetInstance()
				{
					if(m_instance)return m_instance;				
				}
			};
		}
	}
}