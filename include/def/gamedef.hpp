// Copyright (C) 2016 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef GAMEDEF_HPP
#define GAMEDEF_HPP

#include <array>

namespace Def
{

constexpr unsigned MAPX           { 15u }; // For arrays
constexpr unsigned MAPY           { 8u };

constexpr unsigned TILEARRAYSIZE  { MAPX * MAPY };
constexpr  float   TILESETSIZE    { 256 };

constexpr unsigned LMAPX          { 14u }; // For logic
constexpr unsigned LMAPY          { 15u };

constexpr unsigned TILEXSIZE      { 64u }; // For logic
constexpr unsigned TILEYSIZE      { 32u };

constexpr unsigned TILEGXSIZE     { TILEXSIZE / 2 };
constexpr unsigned TILEGYSIZE     { TILEYSIZE / 2 };

constexpr unsigned MAXPOSINTILE   { 4u };
constexpr unsigned MAXGXPOSINTILE { TILEGXSIZE / MAXPOSINTILE };
constexpr unsigned MAXGYPOSINTILE { TILEGYSIZE / MAXPOSINTILE };

constexpr  float   MAXFPS         { 10 }; // Updates per second

constexpr   int    MAXDIR         { 4 }; // Max directions: Up, down, left, right

constexpr  auto    DEFAULTMAPTILESET { ":/game/tileset" };

constexpr std::array<int,   8> MAP_DISTANCE_X    { 0,   2,   0 , -2,   1,   -1,    1,   -1    };
constexpr std::array<int,   8> MAP_DISTANCE_Y    { 2,   0,  -2,   0,   1,   -1,   -1,    1    };
constexpr std::array<float, 8> MAP_DISTANCE_COST { 2.f, 2.f, 2.f, 2.f, 1.5f, 1.5f, 1.5f, 1.5f };

}

#endif // GAMEDEF_HPP
