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
    explicit CameraComponent(Actor* owner, int updateOrder, float viewWidth, float viewHeight);

    void Update(float deltaTime) override;

private:
    SDL_FRect* mView{nullptr};

    Vector2 mPosition{Vector2::Zero};

};


#endif //CAMERACOMPONENT_H
