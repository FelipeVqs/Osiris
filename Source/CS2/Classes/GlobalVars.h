#pragma once

// Adding a guard clause to prevent multiple inclusions of the same header
#ifndef GLOBALVARS_H
#define GLOBALVARS_H

// Including the necessary headers
#include <cstddef> // for std::size_t
#include <Utils/Pad.h>

namespace cs2
{

// Using std::size_t for the pad size to ensure portability
using PadSize = std::size_t;

// Defining a struct to represent the padding
struct GlobalVarsPad
{
    PAD(44);
};

// Defining the GlobalVars struct with a single float member and a padding member
struct GlobalVars
{
    float curtime;
    GlobalVarsPad pad;
};

} // namespace cs2

// Adding the guard clause endif to prevent multiple inclusions of the same header
#endif // GLOBALVARS_H
