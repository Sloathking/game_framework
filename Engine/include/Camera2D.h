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

private:

};

#endif //CAMERA2D_H
