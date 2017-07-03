﻿// Copyright (C) 2016 Samy Bensaid
// This file is part of the TealDemo project.
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef ATTACKRESISTANCECOMPONENT_HPP
#define ATTACKRESISTANCECOMPONENT_HPP

#include <Nazara/Core/String.hpp>
#include <NDK/Component.hpp>
#include <unordered_map>
#include "data/elementdata.hpp"
#include "def/typedef.hpp"
#include "util/variant.hpp"
#include "util/assert.hpp"

struct ResistanceModifierComponent : public Ndk::Component<ResistanceModifierComponent>
{
    ResistanceModifierComponent(int n = 0, int a = 0, int f = 0, int w = 0, int e = 0)
    {
        data[Element::Neutral] = n;
        data[Element::Air] = a;
        data[Element::Fire] = f;
        data[Element::Water] = w;
        data[Element::Earth] = e;
    }

    ResistanceModifierComponent(const LuaArguments& arguments)
    {
        TealException(arguments.size() <= 5, "Too much arguments !");

        Element e {};

        for (auto& variant : arguments)
        {
            data[e] = static_cast<int>(variant.get<double>());
            ++e;

            if (e > Element::Max)
                break;
        }
    }

    ~ResistanceModifierComponent() = default;

    std::unordered_map<Element, int> data;

    static Ndk::ComponentIndex componentIndex;
};

#endif // ATTACKRESISTANCECOMPONENT_HPP
