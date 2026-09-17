//
// Created by sloath on 27-Aug-26.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component.h"
#include "Math.h"

class CameraComponent : public Component
{
public:
    explicit CameraComponent(class Actor* owner, int updateOrder = 200);

protected:
    void SetViewMatrix(const Matrix4& view) const;

};

#endif //CAMERACOMPONENT_H
