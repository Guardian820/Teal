﻿// Copyright (C) 2016 Samy Bensaid
// This file is part of the Teal game.
// For conditions of distribution and use, see copyright notice in LICENSE

#include "global.hpp"

DiffTile DirToXY(DirectionFlags d)
{
    auto pos = toUnderlyingType(DirToOrient(d));
    int x = Def::MAP_DISTANCE_X[pos];
    int y = Def::MAP_DISTANCE_Y[pos];

    return { x, y };
}

DirectionFlags XYToDir(DiffTile d)
{
    int x { d.x };
    int y { d.y };

    TealAssert((x != 0 || y != 0), "x and y may not be 0");

    auto dir = Dir::Up; // Must put a default value

    for (unsigned i {}; i < Def::MAP_DISTANCE_X.size(); ++i)
    {
        if (x == Def::MAP_DISTANCE_X[i] && y == Def::MAP_DISTANCE_Y[i])
            return OrientToDir(static_cast<Orientation>(i));
    }

    return dir;
}

Orientation DirToOrient(DirectionFlags d)
{
    TealAssert(d, "No flag set !");

    if ((d & Dir::DownLeft) == Dir::DownLeft)
        return Orientation::DownLeft;

    if ((d & Dir::DownRight) == Dir::DownRight) // Okay, my fault...
        return Orientation::DownRight;

    if ((d & Dir::UpLeft) == Dir::UpLeft)
        return Orientation::UpLeft;

    if ((d & Dir::UpRight) == Dir::UpRight)
        return Orientation::UpRight;


    if ((d & Dir::Down) == Dir::Down)
        return Orientation::Down;

    if ((d & Dir::Up) == Dir::Up)
        return Orientation::Up;

    if ((d & Dir::Left) == Dir::Left)
        return Orientation::Left;

    if ((d & Dir::Right) == Dir::Right)
        return Orientation::Right;

    return {}; // Oh, well...
}

DirectionFlags OrientToDir(Orientation o)
{
    switch (o)
    {
    case Orientation::Down:
        return Dir::Down;
        break;

    case Orientation::Up:
        return Dir::Up;
        break;

    case Orientation::Left:
        return Dir::Left;
        break;

    case Orientation::Right:
        return Dir::Right;
        break;

    case Orientation::DownLeft:
        return Dir::DownLeft;
        break;

    case Orientation::DownRight:
        return Dir::DownRight;
        break;

    case Orientation::UpLeft:
        return Dir::UpLeft;
        break;

    case Orientation::UpRight:
        return Dir::UpRight;
        break;
    }

    TealAssert(false, "No flag set !");
    return {};
}

bool isDiagonal(DirectionFlags dir)
{
    bool diag = true;

    if (dir == Dir::Right
     || dir == Dir::Down
     || dir == Dir::Left
     || dir == Dir::Up)
        diag = false;

    return diag;
}
