//
// Created by sloath on 18-Sep-26.
//

#ifndef FOLLOWCAMERA_H
#define FOLLOWCAMERA_H

#include "CameraComponent.h"

class FollowCamera : public CameraComponent
{
public:
    explicit FollowCamera(Actor* owner);

    void Update(float deltaTime) override;

    void SnapToIdeal();

    // getters // setters
    void SetHorizontalDist(const float dist) { mHorizontalDist = dist; }

    void SetVerticalDist(const float dist) { mVerticalDist = dist; }

    void SetTargetDist(const float dist) { mTargetDist = dist; }

    void SetSpringConstant(const float spring) { mSpringConstant = spring; }

private:
    [[nodiscard]] Vector3 ComputeCameraPos() const;

    Vector3 mActualPos{Vector3::Zero};

    Vector3 mVelocity{Vector3::Zero};

    float mHorizontalDist{0.0f};

    float mVerticalDist{0.0f};

    float mTargetDist{0.0f};

    float mSpringConstant{0.0f};

};


#endif //FOLLOWCAMERA_H
