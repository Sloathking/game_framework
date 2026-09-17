//
// Created by sloath on 17-Sep-26.
//

#ifndef FPSACTOR_H
#define FPSACTOR_H

#include <Engine/include/Actor.h>

class FPSActor : public Actor
{
public:
    explicit FPSActor(class Game* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class MoveComponent* mMoveComp;
    class FPSCamera* mCam;
    class MeshComponent* mMesh;
    Actor* mFPSModel;

};


#endif //FPSACTOR_H
