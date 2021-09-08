#pragma once

#include <unordered_map>
#include <SDL_scancode.h>

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

    struct State {
        bool hasPressedKey = false;
        Key keyPressed = Key::NONE;
    };

    struct Keyboard
    {
        static inline bool IsValid(const Key key) {
            return key != Key::NONE;
        }

        State m_state;
        const std::unordered_map<SDL_Scancode, Key> m_keymap = {
            { SDL_SCANCODE_KP_1, Key::KEY_1 },
            { SDL_SCANCODE_KP_2, Key::KEY_2 },
            { SDL_SCANCODE_KP_3, Key::KEY_3 },
            { SDL_SCANCODE_KP_4, Key::KEY_4 },
            { SDL_SCANCODE_KP_5, Key::KEY_5 },
            { SDL_SCANCODE_KP_6, Key::KEY_6 },
            { SDL_SCANCODE_KP_7, Key::KEY_7 },
            { SDL_SCANCODE_KP_8, Key::KEY_8 },
            { SDL_SCANCODE_KP_9, Key::KEY_9 },
            { SDL_SCANCODE_KP_0, Key::KEY_0 },
            { SDL_SCANCODE_A, Key::KEY_A },
            { SDL_SCANCODE_Z, Key::KEY_B },
            { SDL_SCANCODE_E, Key::KEY_C },
            { SDL_SCANCODE_Q, Key::KEY_D },
            { SDL_SCANCODE_S, Key::KEY_E },
            { SDL_SCANCODE_D, Key::KEY_F }
        };
    };
}
