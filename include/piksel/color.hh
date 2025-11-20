#pragma once

namespace piksel 
{

struct Color 
{
    float r, g, b, a;

    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Black;
    static const Color White;
};

constexpr Color Color::Red {1.0f, 0.0f, 0.0f, 1.0f};
constexpr Color Color::Green {0.0f, 1.0f, 0.0f, 1.0f};
constexpr Color Color::Blue {0.0f, 0.0f, 1.0f, 1.0f};
constexpr Color Color::Black {0.0f, 0.0f, 0.0f, 1.0f};
constexpr Color Color::White {1.0f, 1.0f, 1.0f, 1.0f};

} 
