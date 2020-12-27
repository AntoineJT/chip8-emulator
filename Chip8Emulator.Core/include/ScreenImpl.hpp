#pragma once
#include "Screen.hpp"

namespace Chip8
{
    struct ScreenImpl : Screen
    {
        ScreenImpl(const SDL2::SDL& sdl, std::uint8_t ratio) noexcept;
        void Render(const PixelGrid& grid) const override;
        void ChangeBgColor(SDL_Color color, bool fullRefresh) noexcept override;
        void Refresh(bool fullRefresh) noexcept override;
        void DrawPoints(SDL_Color color, const std::vector<SDL_Rect>& rects) const noexcept override;
        void DrawSprite(const std::vector<Point>& pixelsOn) override;
    };
}
