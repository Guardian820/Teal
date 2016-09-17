// Copyright (C) 2016 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef MAPCOMPONENT_HPP
#define MAPCOMPONENT_HPP

#include <NDK/Component.hpp>
#include <NDK/EntityOwner.hpp>
#include <NDK/World.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <Nazara/Utility/Mesh.hpp>
#include <Nazara/Utility/StaticMesh.hpp>
#include <Nazara/Utility/VertexMapper.hpp>
#include <Nazara/Utility/IndexMapper.hpp>
#include <Nazara/Graphics/Model.hpp>
#include <Nazara/Graphics/Material.hpp>
#include <Nazara/Math/Vector2.hpp>
#include "micropather.h"
#include "data/mapdata.hpp"
#include "util.hpp"

///
/// \class MapComponent
///
/// \brief Map of the game
///        Only one instance of it should exist
///

class MapComponent : public Ndk::Component<MapComponent>, public micropather::Graph
{
public:
    MapComponent(const MapData& data, const Ndk::WorldHandle& world);

    MapComponent(const MapComponent&) = default;
    MapComponent& operator=(const MapComponent&) = default;

    MapComponent(MapComponent&&) = default;
    MapComponent& operator=(MapComponent&&) = default;

    ~MapComponent() = default;

    OLDTILEARRAY map;
    OLDTILEARRAY obs;
    //0 = can pass, 1 = can't pass but can view through (in fight), 2 = can't pass and can't view through

    Nz::MaterialRef m_mat; // Tileset
    Nz::MeshRef m_mesh; // Mesh to update when map changed
    Nz::ModelRef m_model; // Use SetMesh when mesh changed

    bool update();
    void init(const Nz::String& tileset, const Ndk::WorldHandle& world);

    //Utility
    inline static void NodeToXY(void* node, unsigned& x, unsigned& y);
    inline static void* XYToNode(unsigned x, unsigned y);
    inline static void XYToArray(unsigned /*x*/, unsigned& y);
    inline static std::pair<unsigned, unsigned> IndexToXY(unsigned index);

    static Ndk::ComponentIndex componentIndex;

private:
    Ndk::EntityOwner m_graphicsMap;

    bool passable(unsigned sX, unsigned sY, unsigned eX, unsigned eY);

    //Micropather
    virtual float LeastCostEstimate(void* nodeStart, void* nodeEnd) override;
    virtual void AdjacentCost(void* node, std::vector<micropather::StateCost>* neighbors) override;
    virtual void PrintStateInfo(void* /*node*/) override {}
};

#endif // MAPCOMPONENT_HPP
