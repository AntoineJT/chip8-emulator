#pragma once
#include <SDL_scancode.h>
#include <SimpleBiMap.hpp>

namespace Chip8
{
    enum class Key
    {
        KEY_1 = 0x1,
        KEY_2 = 0x2,
        KEY_3 = 0x3,
        KEY_4 = 0x4,
        KEY_5 = 0x5,
        KEY_6 = 0x6,
        KEY_7 = 0x7,
        KEY_8 = 0x8,
        KEY_9 = 0x9,
        KEY_0 = 0x0,
        KEY_A = 0xA,
        KEY_B = 0xB,
        KEY_C = 0xC,
        KEY_D = 0xD,
        KEY_E = 0xE,
        KEY_F = 0xF,
        NONE = 0x10
    };

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

    public:
        static bool IsValid(Key key);
        Utils::SimpleBiMap<Key, SDL_Scancode> m_keymap = defaultKeymap;
    };
}
