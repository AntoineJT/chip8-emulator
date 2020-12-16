#pragma once

#include <SDL.h>

namespace SDL2
{
    struct SDL
    {
        // a negative value, implemented with -1
        static constexpr int INIT_FAILURE = -1;
        static constexpr int INIT_SUCCESS = 0;
        static constexpr int ALREADY_RUNNING = 1;

        SDL() = default;
        ~SDL();
        SDL(SDL&&) = default;
        SDL& operator=(SDL&&) = default;

        int Init(Uint32 flags);
        bool Running() const;
        void Quit();

    private:
        bool m_isRunning = false;
    };
};
