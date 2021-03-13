#include "Keyboard.hpp"

bool Chip8::Keyboard::IsValid(Key key)
{
    return key != Key::NONE;
}
