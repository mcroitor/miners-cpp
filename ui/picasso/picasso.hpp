#ifndef _PICASSO_HPP_
#define _PICASSO_HPP_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
  #include <windows.h>
#elif defined(__MINGW32__) || defined(__MINGW64__) || defined(__MSYS__) // MinGW
  #include <windows.h>
#elif defined(__linux__) || defined(__unix__) || defined(ANDROID) // Linux
  #pragma message "Linux is not supported yet"
#endif

#include <string>

#include "color.hpp"
#include "point.hpp"

namespace usm::graphics
{

    /**
     * @brief A simple graphics library for creating a window
     * and drawing basic shapes and text.
     */
    class Picasso
    {
    private:
        uint32_t m_width;
        uint32_t m_height;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) // Windows
        HDC m_hdc;
        HBRUSH m_hbrBackground;
        HBRUSH m_hbrForeground;
#elif __linux__ // Linux
        // #pragma message "Linux is not supported yet"
#endif

    public:
        /**
         * @brief Construct a new Picasso object, creating a window
         *
         * @param width The width of the window
         * @param height The height of the window
         * @param title The title of the window
         */
        Picasso(uint32_t width, uint32_t height, const std::string &title = "Picasso");
        /**
         * @brief Destroy the Picasso object, deleting the window
         */
        ~Picasso();
        /**
         * @brief Set the background color
         *
         * @param color The color
         */
        void SetBackgroundColor(const Color &color);
        /**
         * @brief Set the foreground color
         *
         * @param color The color
         */
        void SetForegroundColor(const Color &color);
        /**
         * @brief Set the font
         *
         * @param fontName The name of the font
         * @param size The size of the font
         */
        void SetFont(const std::string &fontName, uint32_t size);
        /**
         * @brief Draw a line
         *
         * @param start The start point of the line
         * @param end The end point of the line
         */
        void DrawLine(const Point &start, const Point &end);
        /**
         * @brief Draw a line
         *
         * @param x1 The x-coordinate of the start point
         * @param y1 The y-coordinate of the start point
         * @param x2 The x-coordinate of the end point
         * @param y2 The y-coordinate of the end point
         */
        void DrawLine(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
        /**
         * @brief Draw a non-filled rectangle
         *
         * @param x1 The x-coordinate of the top-left corner
         * @param y1 The y-coordinate of the top-left corner
         * @param x2 The x-coordinate of the bottom-right corner
         * @param y2 The y-coordinate of the bottom-right corner
         */
        void DrawRectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
        /**
         * @brief Draw a non-filled rectangle
         *
         * @param topLeft The top-left corner of the rectangle
         * @param bottomRight The bottom-right corner of the rectangle
         */
        void DrawRectangle(const Point &topLeft, const Point &bottomRight);
        /**
         * @brief Draw a non-filled rectangle
         *
         * @param topLeft The top-left corner of the rectangle
         * @param width The width of the rectangle
         * @param height The height of the rectangle
         */
        void DrawRectangle(const Point & topLeft, uint32_t width, uint32_t height);
        /**
         * @brief Fill a rectangle
         *
         * @param x1 The x-coordinate of the top-left corner
         * @param y1 The y-coordinate of the top-left corner
         * @param x2 The x-coordinate of the bottom-right corner
         * @param y2 The y-coordinate of the bottom-right corner
         */
        void FillRectangle(const Point & topLeft, uint32_t width, uint32_t height);
        /**
         * @brief Fill a rectangle
         *
         * @param x1 The x-coordinate of the top-left corner
         * @param y1 The y-coordinate of the top-left corner
         * @param x2 The x-coordinate of the bottom-right corner
         * @param y2 The y-coordinate of the bottom-right corner
         */
        void FillRectangle(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
        /**
         * @brief Fill a rectangle
         * 
         * @param topLeft The top-left corner of the rectangle
         * @param bottomRight The bottom-right corner of the rectangle
         */
        void FillRectangle(const Point &topLeft, const Point &bottomRight);
        /**
         * @brief Draw a circle
         *
         * @param x The x-coordinate of the center of the circle
         * @param y The y-coordinate of the center of the circle
         * @param radius The radius of the circle
         */
        void DrawCircle(uint32_t x, uint32_t y, uint32_t radius);
        /**
         * @brief Draw a circle
         *
         * @param center The center of the circle
         * @param radius The radius of the circle
         */
        void DrawCircle(const Point &center, uint32_t radius);
        /**
         * @brief Fill a circle
         *
         * @param x The x-coordinate of the center of the circle
         * @param y The y-coordinate of the center of the circle
         * @param radius The radius of the circle
         */
        void FillCircle(uint32_t x, uint32_t y, uint32_t radius);
        /**
         * @brief Fill a circle
         *
         * @param center The center of the circle
         * @param radius The radius of the circle
         */
        void FillCircle(const Point &center, uint32_t radius);
        /**
         * @brief Draw text
         *
         * @param x The x-coordinate of the text
         * @param y The y-coordinate of the text
         * @param text The text to draw
         */
        void DrawText(uint32_t x, uint32_t y, const std::string &text);
        /**
         * @brief Draw text
         *
         * @param point The point to draw the text
         * @param text The text to draw
         */
        void DrawText(const Point &point, const std::string &text);

        /**
         * @brief Clear the window
         */
        void Clear();
        /**
         * @brief Get the width of the window
         *
         * @return uint32_t The width of the window
         */
        uint32_t GetWidth() const;
        /**
         * @brief Get the height of the window
         *
         * @return uint32_t The height of the window
         */
        uint32_t GetHeight() const;
        /**
         * @brief Show the window
         */
        void Show();
    };
}

#endif // _PICASSO_HPP_