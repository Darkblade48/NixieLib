#pragma once
#include "NixieDisplay.h"
#include "NixieEffect.h"
#include "NixieEffectsLibrary.h"
#include "NixieModels.h"

template <class Model>
using NixieDisplay = Nixie::Display<Model>;

template <class Model>
using NixieEffect = Nixie::Effect<Model>;

template <class Model>
using NixieEffect_DigitSpin = Nixie::Effect_DigitSpin<Model>;

template <class Model>
using NixieEffect_Crossfade = Nixie::Effect_Crossfade<Model>;

template <class Model>
using NixieEffect_Displace = Nixie::Effect_Displace<Model>;

template <class Model>
using NixieEffect_Glitch = Nixie::Effect_Glitch<Model>;

template <class Model>
using NixieEffect_SmoothChange = Nixie::Effect_SmoothChange<Model>;

template <class Model>
using NixieEffect_SlotMachine = Nixie::Effect_SlotMachine<Model>;

template <class Model>
using NixieEffect_Embers = Nixie::Effect_Embers<Model>;

using Shield4IN14 = Nixie::Shield4IN14;
using Shield5IN14 = Nixie::Shield5IN14;
using Shield6IN14 = Nixie::Shield6IN14;
using Shield8IN14 = Nixie::Shield8IN14;
