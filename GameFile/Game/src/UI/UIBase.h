/**
 * UIBase.h
 *
 * UIの基底クラス
 */
#pragma once


namespace nsApp
{
	namespace nsUI
	{
		class UIBase :public Noncopyable
		{
		public:
			/** トランスフォーム */
			Transform m_transform;


		public:
			/** コンストラクタ */
			UIBase();
			/** デストラクタ */
			virtual ~UIBase();


		public:
			/** 初期化処理 */
			virtual bool Start() = 0;
			/**更新処理*/ 
			virtual void Update() = 0;
			/** 描画処理 */
			virtual void Render(RenderContext& rc) = 0;
		};
		

		/*****************************************/


		/**
		 * 画像を使用するUIの基底クラス
		 */
		class ImageUI :public UIBase
		{
		protected:
			SpriteRender m_image;


		private:
			using SuperClass = UIBase;


		public:
			ImageUI();
			virtual ~ImageUI();


		public:
			virtual bool Start()override;
			virtual void Update()override;
			virtual void Render(RenderContext& rc)override;


		public:
			/** 画像の初期化 */
			void Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation);
			/** 画像に色を乗算 */
			inline void SetMulColor(const Vector4& color) { m_image.SetMulColor(color); }
			/** 画像の基点を設定 */
			inline void SetPivot(const Vector2& pivot) { m_image.SetPivot(pivot); }
			/** 画像をサイズを設定 */
			inline void SetSize(const float width, const float height) { m_transform.m_localScale = Vector3(width, height, 0.0f); }
		};


		/*****************************************/

		/**
		 * ゲージUI
		 */
		class GageUI :public ImageUI
		{
		public:
			GageUI();
			~GageUI();


		public:
			bool Start()override;
			void Update()override;
			void Render(RenderContext& rc)override;


		public:
			/** 画像の横幅を補完率で拡縮 */
			void SetImageScale(const float t) { m_image.SetScale(Vector3(t, 1.0f, 1.0f)); }
		};


		/*****************************************/


		/**
		 * 文字を使用するUIの基底クラス
		 */
		class StringUI :public UIBase
		{
		protected:
			FontRender m_string;



		private:
			using SuperClass = UIBase;


		public:
			StringUI();
			virtual ~StringUI();


		public:
			virtual bool Start()override;
			virtual void Update()override;
			virtual void Render(RenderContext& rc)override;


		public:
			/** 画像の初期化 */
			void Initialize(const wchar_t* string, const float size, const Vector3& position, const Vector4& color, const Vector2& pivot, const float rotation);

			/** 文字列の更新 */
			inline void UpdateText(const wchar_t* string) { m_string.SetText(string); }
		};


		/*****************************************/


		/**
		 * UIを表示するキャンバス
		 */
		class UICanvas :public UIBase
		{
		private:
			using SuperClass = UIBase;

			/** 
			 *画像などのリスト
			 * NOTE: 画像データを部品ごとに格納するリスト
			 */
			std::vector<UIBase*> m_uiList;


		public:
			UICanvas();
			~UICanvas();

			virtual bool Start()override;
			virtual void Update()override;
			virtual void Render(RenderContext& rc)override;


		public:
			template <typename T>
			T* CreateUI()
			{
				T* ui = new T();
				ui->m_transform.SetParent(&m_transform);
				m_uiList.push_back(ui);
				return ui;
			}
		};


		/*****************************************/


		/**
		 * 数字を画像で表示するクラス
		 */
		class NumberUI :public UIBase
		{
		protected:
			/** 数字の画像の配列 */
			std::vector<SpriteRender*>m_numbers;

		private:
			using SuperClass = UIBase;

			/** 記憶する数列 */
			uint16_t m_number = 0;


		public:
			NumberUI();
			virtual ~NumberUI();


		public:
			virtual bool Start()override;
			virtual void Update()override;
			virtual void Render(RenderContext& rc)override;


		public:
			/** 数列の初期化 */
			void Initialize(const char* assetName, const uint16_t drawNumber, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation);
			/** 数列を更新 */
			void NumberUpdate(const char* assetName, const uint16_t drawNumber, const float width, const float height);
			/** 色を設定 */
			void SetColor(const Vector4& color) { for (auto* number : m_numbers)number->SetMulColor(color); }
			/** 指定した桁の数字をとる */
			uint8_t GetNumberOfDigits(const uint16_t number, const uint8_t digit);
		};
	}
}


