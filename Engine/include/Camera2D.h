//
// Created by sloath on 24-Sep-26.
//

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "CameraComponent.h"

class Camera2D : public CameraComponent
{
public:
    explicit Camera2D(class Actor2D* owner);

    void Update(float deltaTime) override;

    // getters / setters
    [[nodiscard]] Vector2 GetWindowSize() const { return Vector2(mWindowWidth, mWindowHeight); }
    void SetWindowSize(const float width, const float height) { mWindowWidth = width; mWindowHeight = height; }

    [[nodiscard]] Vector2 GetPosition() const;

private:
    float mWindowWidth{0.0};
    float mWindowHeight{0.0};

};

#endif //CAMERA2D_H
