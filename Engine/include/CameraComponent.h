//
// Created by sloath on 27-Aug-26.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "Constants.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
    explicit CameraComponent(Actor* owner, int updateOrder = 100);

    void Update(float deltaTime) override;

    [[nodiscard]] Vector2 GetWindowSize() const { return mWindowSize; }
    void SetWindowSize(const Vector2 size) { mWindowSize = size; }

    [[nodiscard]] Vector2 GetPosition() const;

private:
    Vector2 mWindowSize{windowWidth, windowHeight};

};


#endif //CAMERACOMPONENT_H
