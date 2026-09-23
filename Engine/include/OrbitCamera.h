//
// Created by sloath on 22-Sep-26.
//

#ifndef ORBITCAMERA_H
#define ORBITCAMERA_H

#include "CameraComponent.h"

class OrbitCamera : public CameraComponent
{
public:
    explicit OrbitCamera(Actor* owner);

    void Update(float deltaTime) override;

    // getters / setters
    [[nodiscard]] Vector3 GetOffset() const { return mOffset; }
    void SetOffset(const Vector3 offset) { mOffset = offset; }

    [[nodiscard]] float GetPitchSpeed() const { return mPitchSpeed; }
    void SetPitchSpeed(const float speed) { mPitchSpeed = speed; }

    [[nodiscard]] float GetYawSpeed() const { return mYawSpeed; }
    void SetYawSpeed(const float speed) { mYawSpeed = speed; }

private:
    Vector3 mOffset{Vector3::Zero};
    Vector3 mUp{Vector3::UnitZ};

    float mPitchSpeed{0.0f};
    float mYawSpeed{0.0f};

};

#endif //ORBITCAMERA_H
