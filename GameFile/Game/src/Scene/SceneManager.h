/**
 * SceneManager.cpp
 *
 * ゲーム全体のシーンの進行を管理するクラス
 */
#pragma once
#include "src/Scene/IScene.h"
#include <map>
#include <functional>


namespace nsApp
{
	namespace nsScene
	{
		class IScene;
#ifdef K2_DEBUG
		class DebugScene;
#endif


		/**
		 * ゲーム全体のシーンの流れを管理するクラス
		 */
		class SceneManager
		{
		private:
			friend class SceneManagerObject;


		private:
			/** 現在のシーン */
			IScene* m_currentScene = nullptr;
			/** シーンのマップ */
			using SceneMap = std::map<uint32_t, std::function<IScene* ()>>;
			SceneMap m_sceneMap;

#ifdef K2_DEBUG
			/** デバッグシーンのポインタ */
			DebugScene* m_debugScene = nullptr;
#endif


		private:
			SceneManager();
			~SceneManager();


		public:
			void Update();


		private:
			/** シーン追加 */
			template <typename T>
			inline void AddSceneMap()
			{
				m_sceneMap.emplace(T::ID(), []()
					{
						return new T();
					});
			}
			/** シーン追加 */
			void CreateScene(const uint32_t id);


		private:
			/** 自身のインスタンス */
			static SceneManager* m_instance;


		public:
			/** SceneManagerクラスのインスタンスを作成 */
			static void CreateInstance()
			{
				if (m_instance == nullptr)
				{
					m_instance = new SceneManager();
				}
			}
			/** SceneManagerクラスのインスタンスを削除 */
			static void DeleteInstance()
			{
				if (m_instance != nullptr)
				{
					delete m_instance;
					m_instance = nullptr;
				}
			}
			/** BattleManagerクラスのインスタンスを取得 */
			static SceneManager* GetInstance() { return m_instance; }
		};


		/*****************************************************************/


		/**
		 * シーン管理を処理するクラス
		 */
		class SceneManagerObject : public IGameObject
		{
		public:
			SceneManagerObject();
			~SceneManagerObject();


		public:
			bool Start() override;
			void Update() override;
		};
	}
}