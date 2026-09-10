//
// Created by sloath on 09-Sep-26.
//

#ifndef ACTOR2D_H
#define ACTOR2D_H

#include "Actor.h"
#include "Math.h"

class Actor2D : public Actor
{
public:
    explicit Actor2D(Engine* game);

    // Updates World Scale, Rotation, and Location
    void ComputeWorldTransform() override;

    // update function called from Game (not overridable)
    void Update(float deltaTime) override;

    virtual void UpdateActor(float deltaTime);

    // actor-specific handling
    void ActorInput(const InputState& state) override;

    // getters / setters
    [[nodiscard]] Matrix4 GetWorldTransform() const { return mWorldTransform; }

    void SetScale(const float scale) override { mScale = scale; mRecomputeWorldTransform = true; }

    [[nodiscard]] float GetRotation() const { return mRotation; }
    void SetRotation(const float rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

    [[nodiscard]] const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

    [[nodiscard]] Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), Math::Sin(mRotation)); }

protected:

private:
    Matrix4 mWorldTransform{Matrix4::Identity};
    bool mRecomputeWorldTransform{true};

    float mRotation{0.0f};          	// rotation angle (in radians)
    Vector2 mPosition{Vector2::Zero};	// position of Actor
};

#endif //ACTOR2D_H
