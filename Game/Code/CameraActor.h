//
// Created by sloath on 14-Sep-26.
//

#ifndef CAMERAACTOR_H
#define CAMERAACTOR_H

#include <Engine/include/Actor3D.h>

class CameraActor : public Actor3D
{
public:
    explicit CameraActor(class Game* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

private:
    class MoveComponent3D* mMoveComp;

};

#endif //CAMERAACTOR_H
