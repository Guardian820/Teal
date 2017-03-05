﻿// Copyright (C) 2016 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#include "systems/aisystem.hpp"

AISystem::AISystem()
{
    Requires<PathComponent, PositionComponent, MoveToComponent>();
}

AISystem::AISystem(const std::shared_ptr<micropather::MicroPather>& pather)
    : AISystem()
{
    setPather(pather);
}

void AISystem::reset()
{
    NazaraAssert(m_pather, "Pather is null, cannot reset it !");
    m_pather->Reset();
}

void AISystem::setPather(const std::shared_ptr<micropather::MicroPather>& pather)
{
    m_pather = pather;
}

void AISystem::OnUpdate(float elapsed)
{
    NazaraUnused(elapsed);

    for (auto& e : GetEntities())
    {
        auto& path = e->GetComponent<PathComponent>().path;
        auto& pos = e->GetComponent<PositionComponent>();
        auto& move = e->GetComponent<MoveToComponent>();

        if (move.diffX == 0 && move.diffY == 0)
            continue; // This entity doesn't want to move.

        if (pos.moving && !isPositionValid({ pos.x, pos.y }) && pos.inX == 0 && pos.inY == 0)
            continue; // Invalid position, can't stop it

        // Ok, let's do the path.
        NazaraAssert(m_pather, "Pather is null, cannot compute path !");

        // Compute the path with the position and the move component.
        std::vector<void*> voidPath;
        float totalCost {}; // In case of debugging

        int endX { static_cast<int>(pos.x) + move.diffX },
            endY { static_cast<int>(pos.y) + move.diffY };

        int result = m_pather->Solve(MapInstance::XYToNode(pos.x, pos.y),
                                     MapInstance::XYToNode(endX, endY),
                                     &voidPath, &totalCost); // returns the absolute position, not difference.
        
        if (result != 0)
        {
            move.diffX = 0;
            move.diffY = 0;

            continue;
        }

        // Path done, in void*. Let's add it to the entity's path, in integers
        int oldX {};
        int oldY {};

        AbsTile startPos { pos.x, pos.y };
        AbsTile lastPos {};

        std::queue<std::pair<DirectionFlags, bool>> newPath;

        for (std::size_t i {}; i < voidPath.size(); ++i)
        {
            if (i == 0) // First tile is actually the position (micropather's fault)
                continue;

            auto node = voidPath[i];

            unsigned absX {}, absY {}; // Absolute position, not difference
            MapInstance::NodeToXY(node, absX, absY);

            int startX { static_cast<int>(pos.x) };
            int startY { static_cast<int>(pos.y) };

            if (i > 1) // If i == 1 we use the initial position
            {          // Else we use the position micropather generated before
                startX = oldX;
                startY = oldY;
            }

            int diffX { startX - static_cast<int>(absX) },
                diffY { startY - static_cast<int>(absY) }; // Difference now, but reversed

            diffX = -diffX; // Ok
            diffY = -diffY;

            auto dir = XYToDir({ diffX, diffY });
            bool reExec = !isDiagonal(dir);

            newPath.push(std::make_pair(dir, reExec));

            oldX = static_cast<int>(absX);
            oldY = static_cast<int>(absY);

            if (i == (voidPath.size() - 1))
                lastPos = { absX, absY };
        }

        auto currentPath = directionsToPositions(path, startPos);

        move.diffX = 0;
        move.diffY = 0;

        if (!currentPath.empty() && lastPos == currentPath.back())
            continue;

        path = newPath;

        pos.inX = 0;
        pos.inY = 0;
    }
}
