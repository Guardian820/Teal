// Copyright (C) 2016 Samy Bensaid
// This file is part of the Teal game.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef UTIL_HPP
#define UTIL_HPP

#include <Nazara/Graphics/Sprite.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <Nazara/Core/Color.hpp>
#include <Nazara/Utility/Image.hpp>

#include <cassert>
#include <array>
#include "gamedef.hpp"
#include "global.hpp"

inline unsigned dToU(double d);

template<class T>
inline T distance(const T& x, const T& y);

///
/// \fn getRenderableFromGraphicsComponent
///
/// \brief Returns the first renderable it found in the Graphics Component
///        or nullptr if it didn't found one
///
/// \param gfx Graphics Component to search into
///

template<class T>
inline T* getRenderableFromGraphicsComponent(Ndk::GraphicsComponent& gfx);

///
/// \fn getTileFromGlobalCoords
///
/// \brief Returns the tile located at the coords position
///
/// \param coords Global Coordinates of the tile (like mouse position)
///
/// \returns The logic position of the tile
///
/// \note Needs a scheme set with the setScheme function
///
/// \todo Add the z axis ?
///

extern AbsTile getTileFromGlobalCoords(const Nz::Vector2ui& coords);

///
/// \fn setScheme
///
/// \brief Sets the scheme the getTileFromGlobalCoords function will use
///
/// \todo Delete this function and find a better way
///

extern void setScheme(Nz::ImageRef newScheme);

#endif // UTIL_HPP

#include "util.inl"
