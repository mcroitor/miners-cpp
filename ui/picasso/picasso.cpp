#include "picasso.hpp"

namespace usm::graphics
{

    Picasso::Picasso(uint32_t width, uint32_t height, const std::string &title)
    {
        m_width = width;
        m_height = height;
        m_hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
        m_hbrForeground = CreateSolidBrush(RGB(0, 0, 0));
        WNDCLASS wc = {0};
        wc.lpfnWndProc = DefWindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName = title.c_str();
        RegisterClass(&wc);
        HWND hwnd = CreateWindow(title.c_str(), title.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, GetModuleHandle(NULL), NULL);
        ShowWindow(hwnd, SW_SHOW);
        m_hdc = GetDC(hwnd);
    }

    Picasso::~Picasso()
    {
        ReleaseDC(FindWindow(NULL, NULL), m_hdc);
        DeleteObject(m_hbrBackground);
        DeleteObject(m_hbrForeground);
    }

    void Picasso::SetBackgroundColor(const Color &color)
    {
        DeleteObject(m_hbrBackground);
        m_hbrBackground = CreateSolidBrush(color.Value());
    }

    void Picasso::SetForegroundColor(const Color &color)
    {
        DeleteObject(m_hbrForeground);
        m_hbrForeground = CreateSolidBrush(color.Value());
        SetTextColor(m_hdc, color.Value());
    }

    void Picasso::SetFont(const std::string &fontName, uint32_t size)
    {
        HFONT hfont = CreateFont(
            size,
            0,
            0,
            0,
            FW_NORMAL,
            FALSE,
            FALSE,
            FALSE,
            ANSI_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH,
            fontName.c_str());
        SelectObject(m_hdc, hfont);
    }

    void Picasso::DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
    {
        SelectObject(m_hdc, m_hbrForeground);
        MoveToEx(m_hdc, x1, y1, NULL);
        LineTo(m_hdc, x2, y2);
    }

    void Picasso::DrawLine(const Point &start, const Point &end)
    {
        DrawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());
    }

    void Picasso::DrawRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        DrawLine(x, y, x + width, y);
        DrawLine(x + width, y, x + width, y + height);
        DrawLine(x + width, y + height, x, y + height);
        DrawLine(x, y + height, x, y);
    }

    void Picasso::DrawRectangle(const Point &topLeft, const Point &bottomRight)
    {
        DrawRectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX() - topLeft.GetX(), bottomRight.GetY() - topLeft.GetY());
    }

    void Picasso::DrawRectangle(const Point &topLeft, uint32_t width, uint32_t height)
    {
        DrawRectangle(topLeft.GetX(), topLeft.GetY(), width, height);
    }

    void Picasso::FillRectangle(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        SelectObject(m_hdc, m_hbrForeground);
        Rectangle(m_hdc, x, y, x + width, y + height);
    }

    void Picasso::FillRectangle(const Point &topLeft, const Point &bottomRight)
    {
        FillRectangle(topLeft.GetX(), topLeft.GetY(), bottomRight.GetX() - topLeft.GetX(), bottomRight.GetY() - topLeft.GetY());
    }

    void Picasso::FillRectangle(const Point &topLeft, uint32_t width, uint32_t height)
    {
        FillRectangle(topLeft.GetX(), topLeft.GetY(), width, height);
    }

    void Picasso::DrawCircle(const Point &center, uint32_t radius)
    {
        DrawCircle(center.GetX(), center.GetY(), radius);
    }

    void Picasso::DrawCircle(uint32_t x, uint32_t y, uint32_t radius)
    {
        HBRUSH hbrOld = (HBRUSH)SelectObject(m_hdc, GetStockObject(NULL_BRUSH));
        Ellipse(m_hdc, x - radius, y - radius, x + radius, y + radius);
        SelectObject(m_hdc, hbrOld);
    }

    void Picasso::FillCircle(uint32_t x, uint32_t y, uint32_t radius)
    {
        SelectObject(m_hdc, m_hbrForeground);
        Ellipse(m_hdc, x - radius, y - radius, x + radius, y + radius);
    }

    void Picasso::FillCircle(const Point &center, uint32_t radius)
    {
        FillCircle(center.GetX(), center.GetY(), radius);
    }

    void Picasso::DrawText(uint32_t x, uint32_t y, const std::string &text)
    {
        TextOut(m_hdc, x, y, text.c_str(), text.length());
    }

    void Picasso::DrawText(const Point &point, const std::string &text)
    {
        DrawText(point.GetX(), point.GetY(), text);
    }

    uint32_t Picasso::GetWidth() const
    {
        return m_width;
    }

    uint32_t Picasso::GetHeight() const
    {
        return m_height;
    }

    void Picasso::Clear()
    {
        SelectObject(m_hdc, m_hbrBackground);
        FillRectangle(0, 0, m_width, m_height);
    }

    void Picasso::Show()
    {
        MSG msg;
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_CLOSE)
            {
                break;
            }
        }
    }
}
