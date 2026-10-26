//
// Created by sloath on 10/16/26.
//

#ifndef ACTOR3D_H
#define ACTOR3D_H

#include "Actor.h"

class Actor3D : public Actor
{
public:
    explicit Actor3D(Engine* game) : Actor(game) {}

    void Update(float deltaTime) override;

    // Updates World Scale, Rotation, and Location
    void ComputeWorldTransform();
    [[nodiscard]] Matrix4 GetWorldTransform() const { return mWorldTransform; }

    [[nodiscard]] Quaternion GetRotation() const { return mRotation; }
    void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true; }

    [[nodiscard]] const Vector3& GetPosition() const { return mPosition; }
    void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }

    [[nodiscard]] Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }
    [[nodiscard]] Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

    void SetScale(const float scale) override { mScale = scale; mRecomputeWorldTransform = true; }

protected:
    std::vector<class Component3D*> mComponents;

    bool mRecomputeWorldTransform{true};
    Matrix4 mWorldTransform{Matrix4::Identity};

    // transform properties
    Quaternion mRotation{Quaternion::Identity};
    Vector3 mPosition{Vector3::Zero};

};

#endif // ACTOR3D_H
