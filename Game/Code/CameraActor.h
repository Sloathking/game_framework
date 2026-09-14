//
// Created by sloath on 14-Sep-26.
//

#ifndef CAMERAACTOR_H
#define CAMERAACTOR_H

#include <Engine/include/Actor.h>

class CameraActor : public Actor
{
public:
    explicit CameraActor(Engine* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

private:
    class MoveComponent* mMoveComp;

};

#endif //CAMERAACTOR_H
