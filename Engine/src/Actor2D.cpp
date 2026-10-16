//
// Created by sloath on 10/16/26.
//

#include "include/Actor2D.h"

void Actor2D::Update(const float deltaTime)
{
    if (mState == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}