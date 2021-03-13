#pragma once
#include <SDL_scancode.h>

#include "Keys.hpp"
#include <SimpleBiMap.hpp>

namespace Chip8
{
    class Keyboard
    {
        static inline std::unordered_map<Key, SDL_Scancode> defaultKeymap = {
            { Key::KEY_1, SDL_SCANCODE_2 },
            { Key::KEY_4, SDL_SCANCODE_W },
            { Key::KEY_7, SDL_SCANCODE_S },
            { Key::KEY_A, SDL_SCANCODE_X },
            { Key::KEY_2, SDL_SCANCODE_3 },
            { Key::KEY_5, SDL_SCANCODE_E },
            { Key::KEY_8, SDL_SCANCODE_D },
            { Key::KEY_0, SDL_SCANCODE_C },
            { Key::KEY_3, SDL_SCANCODE_4 },
            { Key::KEY_6, SDL_SCANCODE_R },
            { Key::KEY_9, SDL_SCANCODE_F },
            { Key::KEY_B, SDL_SCANCODE_V },
            { Key::KEY_C, SDL_SCANCODE_5 },
            { Key::KEY_D, SDL_SCANCODE_T },
            { Key::KEY_E, SDL_SCANCODE_G },
            { Key::KEY_F, SDL_SCANCODE_B }
        };
        Utils::SimpleBiMap<Key, SDL_Scancode> m_keymap = defaultKeymap;

    public:
        static bool IsValid(Key key);
    };
}
