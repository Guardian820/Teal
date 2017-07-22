﻿// Copyright (C) 2016 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#include "util/gfxutil.hpp"

namespace
{

Nz::ImageRef m_scheme {};

}

AbsTile getTileFromGlobalCoords(const Nz::Vector2ui& coords)
{
    TealAssert(m_scheme.IsValid(), "Scheme Ref isn't valid, setScheme() must be used !");
    TealAssert(m_scheme->IsValid(), "Scheme Image isn't valid !");

    unsigned const x { coords.x }, y { coords.y };

    unsigned const rectX { (x / Def::TILEXSIZE) * 2 }; // Rectangle where we clicked
    unsigned const rectY { (y / Def::TILEYSIZE) * 2 }; // We need losange // < bug

    int const iRectX { utoi(rectX) };
    int const iRectY { utoi(rectY) };

    unsigned const rectClickX { x % Def::TILEXSIZE }; // We need the click to see
    unsigned const rectClickY { y % Def::TILEYSIZE }; // where in the rectangle we clicked

    Nz::Color color = m_scheme->GetPixelColor(rectClickX, rectClickY);

    int losangeX { iRectX };
    int losangeY { iRectY };

    bool even = isLineEven(losangeY < 0 ? 0 : losangeY);

    Orientation o = Orientation::Down;


    if (color == Nz::Color::Blue)
        o = Orientation::UpLeft;

    if (color == Nz::Color::Red)
        o = Orientation::UpRight;

    if (color == Nz::Color::Yellow)
        o = Orientation::DownLeft;

    if (color == Nz::Color::Green)
        o = Orientation::DownRight;

    if (color == Nz::Color::White)
        o = Orientation::Up;


    if (o == Orientation::Down)
        NazaraError("Error in scheme !");

    if (o != Orientation::Up)
    {
        losangeX += even ? Def::MAP_DISTANCE_EVEN_X[toUnderlyingType(o)] : Def::MAP_DISTANCE_EVEN_X[toUnderlyingType(o)];
        losangeY += even ? Def::MAP_DISTANCE_EVEN_Y[toUnderlyingType(o)] : Def::MAP_DISTANCE_EVEN_Y[toUnderlyingType(o)];
    }


    // If the tile is negative:
    losangeX = (losangeX < 0) ? 0 : losangeX;
    losangeY = (losangeY < 0) ? 0 : losangeY;

    unsigned fLosangeX { static_cast<unsigned>(losangeX) };
    unsigned fLosangeY { static_cast<unsigned>(losangeY) };

    // If tile is out the map:
    fLosangeX = (fLosangeX > Def::ARRAYMAPX) ? Def::ARRAYMAPX : fLosangeX;
    fLosangeY = (fLosangeY > Def::ARRAYMAPY) ? Def::ARRAYMAPY : fLosangeY;

    return { fLosangeX, fLosangeY };
}

void initSchemeUtility(Nz::ImageRef newScheme)
{
    m_scheme = newScheme;
}

void refreshGraphicsPos(const Ndk::EntityHandle& logicEntity, const Ndk::EntityHandle& graphicalEntity)
{
    TealAssert(isMapEntity(graphicalEntity), "Graphical Entity isn't a graphical entity !");

    auto& pos = logicEntity->GetComponent<PositionComponent>();
    auto& gfxcomp = graphicalEntity->GetComponent<Ndk::GraphicsComponent>();
    auto& gfxpos = graphicalEntity->GetComponent<Ndk::NodeComponent>();
    auto& dpos = graphicalEntity->GetComponent<DefaultGraphicsPosComponent>();

    Nz::Vector2f defPos { dpos.xy };

    unsigned const gX = pos.xy.x * Def::TILEXSIZE + (isLineEven(pos.xy.y) ? 0u : 32u); // convert logic pos to graphics pos
    unsigned const gY = pos.xy.y * Def::TILEYSIZE / 2;

    DiffTile gInXY {};

    if (pos.direction)
    {
        gInXY = DirToGXY(pos.direction);
        gInXY *= pos.advancement;
    }

    float const finalX = static_cast<float>(gX) + static_cast<float>(gInXY.x) + defPos.x; // We will move using this
    float const finalY = static_cast<float>(gY) + static_cast<float>(gInXY.y) + defPos.y; // (so it's graphics pos)

    if (finalX != gfxpos.GetPosition().x || // if the entity is already at that position
        finalY != gfxpos.GetPosition().y) // no need to move it
    {
        float const moveX = finalX - gfxpos.GetPosition().x;
        float const moveY = finalY - gfxpos.GetPosition().y;

        gfxpos.Move(moveX, moveY);
    }
}
