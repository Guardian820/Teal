#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include <QMouseEvent>
#include <type_traits>
#include <assert.h>
#include <stdexcept>
#include "util.hpp"

using Button = Qt::MouseButton;

enum class Orientation
{
    Down,
    DownRight,
    Right,
    UpRight,
    Up,
    UpLeft,
    Left,
    DownLeft
};

namespace Direction
{

enum Direction
{
    Up = 1<<0,
    Down = 1<<1,
    Left = 1<<2,
    Right = 1<<3,

    UpDown = Up | Down,
    LeftRight = Left | Right,

    DownRight = Down | Right,
    UpRight = Up | Right,
    UpLeft = Up | Left,
    DownLeft = Down | Left
};

using Dir = Direction;


extern constexpr Dir operator | (Dir a, Dir b);
extern void operator |= (Dir& a, Dir b);

extern constexpr Dir operator & (Dir a, Dir b);
extern void operator &= (Dir& a, Dir b);

extern Dir operator ~ (Dir a);

}

extern int DirToY(Direction::Dir d);
extern int DirToX(Direction::Dir d);
extern DiffTile DirToXY(Direction::Dir d);

extern Orientation DirToOrien(Direction::Dir d);
extern Direction::Dir OrienToDir(Orientation o);

#endif // GLOBAL_HPP
