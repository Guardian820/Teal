// Copyright (C) 2019 Samy Bensaid
// This file is part of the Teal project.
// For conditions of distribution and use, see copyright notice in LICENSE

#include "components/characters/positioncomponent.hpp"
#include "components/characters/pathcomponent.hpp"
#include "components/characters/orientationcomponent.hpp"
#include "components/characters/fightcomponent.hpp"
#include "components/characters/inventorycomponent.hpp"
#include "util/maputil.hpp"
#include "util/moveutil.hpp"
#include "cache/tilesetcore.hpp"
#include "def/systemdef.hpp"
#include "systems/movementsystem.hpp"

MovementSystem::MovementSystem(const Ndk::EntityHandle& mainCharacter)
    : m_mainCharacter { mainCharacter }
{
    Requires<PathComponent, PositionComponent, OrientationComponent>();
    SetMaximumUpdateRate(Def::MaxSystemUPS);
    SetUpdateOrder(Def::MovementSystemUpdateOrder);
}

void MovementSystem::OnUpdate(float elapsed)
{
    NazaraUnused(elapsed);

    for (auto& e : GetEntities())
    {
        auto& path = e->GetComponent<PathComponent>().path;

        if (path.empty())
            continue;

        bool fightMode = e->HasComponent<FightComponent>() && e->GetComponent<FightComponent>().isFighting;
        moveEntity(e, !fightMode);

        if (path.empty()) // Finished path
            if (e == m_mainCharacter && !fightMode)
            {
                TealAssert(hasComponentsToChangeMap(e) && e->HasComponent<InventoryComponent>(), "Main character doesn't have required components ?");

                getItemsFromGround(e);
                changeMap();
            }
    }
}
