//
// Created by sloath on 17-Sep-26.
//

#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "CameraComponent.h"

class FPSCamera : public CameraComponent
{
public:
    explicit FPSCamera(Actor* owner);

    void Update(float deltaTime) override;

    // getters / setters
    [[nodiscard]] float GetPitch() const { return mPitch; }

    [[nodiscard]] float GetPitchSpeed() const { return mPitchSpeed; }
    void SetPitchSpeed(const float speed) { mPitchSpeed = speed; }

    [[nodiscard]] float GetMaxPitch() const { return mMaxPitch; }
    void SetMaxPitch(const float pitch) {mMaxPitch = pitch; }

private:
    float mPitch{0.0f};

    float mPitchSpeed{0.0f};

    float mMaxPitch{Math::Pi / 3.0f};

};


#endif //FPSCAMERA_H
