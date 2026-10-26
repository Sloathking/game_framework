//
// Created by sloath on 27-Aug-26.
//

#ifndef CAMERACOMPONENT_H
#define CAMERACOMPONENT_H

#include "Component3D.h"
#include "Math.h"

class CameraComponent : public Component3D
{
public:
    explicit CameraComponent(class Actor3D* owner, int updateOrder = 200);

protected:
    void SetViewMatrix(const Matrix4& view) const;

};

#endif //CAMERACOMPONENT_H
