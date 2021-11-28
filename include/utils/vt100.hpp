#pragma once

#include <string>

enum class Color
{
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA = 6,
    CYAN = 7,
    WHITE = 8,
    DEFAULT = 9
};

struct WindowSize
{
    size_t rows;
    size_t cols;
};

struct Cursor
{
    size_t y;
    size_t x;
};

// https://wiki.bash-hackers.org/scripting/terminalcodes
class VT100
{
public:
    static void foregroundColor(Color color);
    static void clearScreen();
    static WindowSize getWindowSize();
    static void fillLine(char c, size_t times);
    static void goTo(Cursor postion);
    static void eraseLine();
};