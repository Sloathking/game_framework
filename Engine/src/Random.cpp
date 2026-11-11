//
// Created by sloath on 17-Aug-26.
//

// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "include/Random.h"

void Random::Init()
{
    std::random_device rd;
    Seed(rd());
}

void Random::Seed(const unsigned int seed)
{
    sGenerator.seed(seed);
}

float Random::GetFloat()
{
    return GetFloatRange(0.0f, 1.0f);
}

float Random::GetFloatRange(const float min, const float max)
{
    std::uniform_real_distribution dist(min, max);
    return dist(sGenerator);
}

int Random::GetIntRange(const int min, const int max)
{
    std::uniform_int_distribution dist(min, max);
    return dist(sGenerator);
}

Vector2 Random::GetVector(const Vector2& min, const Vector2& max)
{
    const auto r = Vector2(GetFloat(), GetFloat());
    return min + (max - min) * r;
}

Vector3 Random::GetVector(const Vector3& min, const Vector3& max)
{
    const auto r = Vector3(GetFloat(), GetFloat(), GetFloat());
    return min + (max - min) * r;
}

std::mt19937 Random::sGenerator;