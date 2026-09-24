//
// Created by sloath on 24-Sep-26.
//

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "CameraComponent.h"

class Camera2D : public CameraComponent
{
public:
    explicit Camera2D(Actor* owner);

    void Update(float deltaTime) override;

    // getters / setters
    [[nodiscard]] Vector3 GetOffset() const { return mOffset; }
    void SetOffset(const Vector3 offset) { mOffset = offset; }

    [[nodiscard]] float GetPitch() const { return mPitch; }
    void SetPitch(const float pitch) { mPitch = pitch; }

private:
    Vector3 mOffset{Vector3::Zero};
    float mPitch{0.0f};

};


#endif //CAMERA2D_H
