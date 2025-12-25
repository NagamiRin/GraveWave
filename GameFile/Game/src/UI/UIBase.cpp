/**
 * UIBase.cpp
 *
 * UIの基底クラス
 */
#include "stdafx.h"
#include "UIBase.h"
#include "src/Transform.h"


namespace nsApp
{
    namespace nsUI
    {
        UIBase::UIBase()
        {
        }

        
        UIBase::~UIBase()
        {
        }

       
        bool UIBase::Start()
        {
            return true;
        }

        
        void UIBase::Update()
        {
            m_transform.UpdateTransform();
        }

        
        void UIBase::Render(RenderContext& rc)
        {
        }


        /*****************************************/


        ImageUI::ImageUI()
        {
            //最初は描画させる
            m_isDraw = true;
        }


        ImageUI::~ImageUI()
        {

        }


        bool ImageUI::Start()
        {
            return true;
        }


        void ImageUI::Update()
        {
            SuperClass::Update();

            m_image.SetPosition(m_transform.m_position);
            m_image.SetScale(m_transform.m_scale);
            m_image.SetRotation(m_transform.m_rotation);
            m_image.Update();
        }


        void ImageUI::Render(RenderContext& rc)
        {
            if (m_isDraw) m_image.Draw(rc);
        }


        void ImageUI::Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
        {
            m_transform.m_localPosition = position;
            m_transform.m_localScale = scale;
            m_transform.m_localRotation = rotation;

            m_image.Init(assetName, width, height);
            m_image.SetPosition(position);
            m_image.SetScale(scale);
            m_image.SetRotation(rotation);
            m_image.Update();
        }




        /*****************************************/


        StringUI::StringUI()
        {

        }


        StringUI::~StringUI()
        {

        }


        bool StringUI::Start()
        {
            return true;
        }


        void StringUI::Update()
        {
            SuperClass::Update();

            m_string.SetPosition(m_transform.m_position);
        }


        void StringUI::Render(RenderContext& rc)
        {
            m_string.Draw(rc);
        }


        void StringUI::Initialize(const wchar_t* string, const float size, const Vector3& position, const Vector4& color, const Vector2& pivot, const float rotation) 
        {
            m_transform.m_localPosition = position;

            m_string.SetText(string);
            m_string.SetScale(size);
            m_string.SetPosition(position);
            m_string.SetColor(color);
            m_string.SetPivot(pivot);            
        }


        /*****************************************/


        UICanvas::UICanvas()
        {

        }


        UICanvas::~UICanvas()
        {
            for (auto* ui : m_uiList)
            {
                delete ui;
            }
            m_uiList.clear();
        }


        bool UICanvas::Start()
        {
            return true;
        }


        void UICanvas::Update()
        {
            m_transform.UpdateTransform();

            for (auto* ui : m_uiList) {
                ui->Update();
            }
        }


        void UICanvas::Render(RenderContext& rc)
        {
            for (auto* ui : m_uiList) {
                ui->Render(rc);
            }
        }


        void UICanvas::Remove(UIBase* ui)
        {
			// uiをリストから削除
            auto it = std::find(m_uiList.begin(), m_uiList.end(), ui);
            if (it != m_uiList.end()) {
                m_uiList.erase(it);
			}
            delete ui;
        }




        /*****************************************/


        NumberUI::NumberUI()
        {
        }


        NumberUI::~NumberUI()
        {
        }


        bool NumberUI::Start()
        {
            return true;
        }


        void NumberUI::Update()
        {
            SuperClass::Update();

            for (int i = 0; i < m_numbers.size();++i) {
                auto* number = m_numbers[i];          
                float pos = (i - 1) * -m_wide + -10.0f;
                number->SetPosition(m_transform.m_position + Vector3(pos, 0.0f, 0.0f));
                number->SetScale(m_transform.m_scale);
                number->SetRotation(m_transform.m_rotation);
                number->Update();
            }
        }


        void NumberUI::Render(RenderContext& rc)
        {
            if (!m_isDraw) return;

            for (auto* number : m_numbers) {
                number->Draw(rc);
            }
        }


        void NumberUI::Initialize(const char* assetName, const uint16_t drawNumber, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation)
        {
            m_transform.m_localPosition = position;
            m_transform.m_localRotation = rotation;
            m_transform.m_localScale = scale;

            m_number = drawNumber;

            //K2_ASSERT(drawNumber > 0, "0はありえない\n");
           
            //桁数を調べる
            uint8_t digit = 0; 
            uint16_t num = 1;
            while(true){
                if (static_cast<float>(drawNumber / num) >= 1.0f)digit++;
                else break;
                num *= 10;
            }

            //桁数が0になっちゃってるとき
            if (digit == 0)digit = 1;

            m_numbers.resize(digit);

            for (int i = 0; i < m_numbers.size(); ++i) {
                std::string path = std::string(assetName) + "/0.DDS";
                path[path.size() - 5] = '0' + GetNumberOfDigits(drawNumber, digit);

                m_numbers[i] = new SpriteRender();
                m_numbers[i]->Init(path.c_str(), width, height);
                m_numbers[i]->SetPosition(position + Vector3(width * (digit - 1), 0.0f, 0.0f));
                m_numbers[i]->SetScale(scale);
                m_numbers[i]->SetRotation(rotation);
            }

            m_wide = width;
        }


        void NumberUI::NumberUpdate(const char* assetName, const uint16_t drawNumber, const float width, const float height)
        {
            if (m_number == drawNumber) return;

            m_number = drawNumber;
            uint8_t digit = 0;
            uint16_t num = 1;
            if (drawNumber == 0)digit = 1;

            while (true) {
                if (static_cast<float>(drawNumber / num) >= 1.0f)digit++;
                else break;
                num *= 10;
            }

            while (m_numbers.size() < digit) {
                m_numbers.push_back(new SpriteRender);
            }
            while (m_numbers.size() > digit) {
                m_numbers.pop_back();
            }

            uint8_t currentDigit = 1;
            for (auto* number : m_numbers) {
                if (number == nullptr) {
                    number = new SpriteRender();
                }
                std::string path = std::string(assetName) + "/0.DDS";
                path[path.size() - 5] = '0' + GetNumberOfDigits(drawNumber, currentDigit);
                
                currentDigit++;

                number->Init(path.c_str(), width, height);
            }

            m_wide = width;
        }


        uint8_t NumberUI::GetNumberOfDigits(const uint16_t number, const uint8_t digit)
        {
            return (number / static_cast<int>(pow(10, digit - 1))) % 10;
        }
}
}