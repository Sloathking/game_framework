//
// Created by sloath on 17-Sep-26.
//

#ifndef FPSACTOR_H
#define FPSACTOR_H

#include <Engine/include/Actor3D.h>

class FPSActor : public Actor3D
{
public:
    explicit FPSActor(class Game* game);

    void UpdateActor(float deltaTime) override;

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class MoveComponent3D* mMoveComp;
    class FPSCamera* mCam;
    class MeshComponent* mMesh{nullptr};
    Actor3D* mFPSModel;

};

#endif //FPSACTOR_H
