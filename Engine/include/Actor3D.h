//
// Created by sloath on 10-Sep-26.
//

#ifndef ACTOR3D_H
#define ACTOR3D_H

#include "Actor.h"
#include "Math.h"

class Actor3D : public Actor
{
public:
    explicit Actor3D(Engine* game);

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

    [[nodiscard]] Quaternion GetRotation() const { return mRotation; }
    void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

    [[nodiscard]] const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

    [[nodiscard]] Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

protected:

private:
    Matrix4 mWorldTransform{Matrix4::Identity};
    bool mRecomputeWorldTransform{true};

    Quaternion mRotation{};
    Vector3 mPosition{Vector3::Zero};
};

#endif //ACTOR3D_H
