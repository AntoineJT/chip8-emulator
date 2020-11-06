#pragma once

#include <SDL.h>

namespace SDL2
{
    struct SDL
    {
        SDL() = default;
        ~SDL();
        int Init(Uint32 flags);

    private:
        bool m_isRunning = false;
    };
};
