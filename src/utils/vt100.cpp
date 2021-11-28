#include <iostream>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "utils/vt100.hpp"

void VT100::foregroundColor(Color color)
{
    switch (color)
    {
    case Color::BLACK:
        std::cout << "\e[30m";
        break;
    case Color::RED:
        std::cout << "\e[31m";
        break;
    case Color::GREEN:
        std::cout << "\e[32m";
        break;
    case Color::YELLOW:
        std::cout << "\e[33m";
        break;
    case Color::BLUE:
        std::cout << "\e[34m";
        break;
    case Color::MAGENTA:
        std::cout << "\e[35m";
        break;
    case Color::CYAN:
        std::cout << "\e[36m";
        break;
    case Color::WHITE:
        std::cout << "\e[37m";
        break;
    case Color::DEFAULT:
    default:
        std::cout << "\e[39m";
        break;
    }
}

void VT100::clearScreen()
{
    WindowSize size = getWindowSize();
    for (size_t i = 0; i < size.rows; ++i)
    {
        std::cout << std::endl;
    }
    std::cout << "\x1b[2J\x1b[H";
}

WindowSize VT100::getWindowSize()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("lines %d\n", w.ws_row);
    printf("columns %d\n", w.ws_col);
    return {.rows = w.ws_row, .cols = w.ws_col};
}

void VT100::fillLine(char c, size_t times)
{
    for (size_t i = 0; i < times; ++i)
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

void VT100::goTo(Cursor postion)
{
    std::cout << "\e[" << postion.y << ";" << postion.x << "H";
}

void VT100::eraseLine()
{
    std::cout << "\e[K";
}