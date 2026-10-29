//
// Created by sloath on 24-Sep-26.
//

#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "Component2D.h"

class Camera2D : public Component2D
{
public:
    explicit Camera2D(Actor2D* owner, int updateOrder = 200);

    void Update(float deltaTime) override;

    // getters / setters
    [[nodiscard]] Vector2 GetWindowSize() const { return Vector2(mWindowWidth, mWindowHeight); }
    void SetWindowSize(const float width, const float height) { mWindowWidth = width; mWindowHeight = height; }

    [[nodiscard]] Vector2 GetPosition() const;
    [[nodiscard]] Vector2 GetCameraOffset(float renderScale) const;

private:
    float mWindowWidth{0.0};
    float mWindowHeight{0.0};

};

#endif //CAMERA2D_H
