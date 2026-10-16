//
// Created by sloath on 10/16/26.
//

#ifndef ACTOR2D_H
#define ACTOR2D_H

#include "Actor.h"

class Actor2D : public Actor
{
public:
    explicit Actor2D(Engine* game) : Actor(game) {}

    void Update(float deltaTime) override;

    // Updates World Scale, Rotation, and Location
    [[nodiscard]] float GetRotation() const { return mRotation; }
    void SetRotation(const float& rotation) { mRotation = rotation; }

    [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }

    [[nodiscard]] Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

    void SetScale(const float scale) override { mScale = scale; }

private:
    // transform properties
    float mRotation{0.0f};
    Vector2 mPosition{Vector2::Zero};

};

#endif // ACTOR2D_H
