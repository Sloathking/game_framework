//
// Created by sloath on 22-Sep-26.
//

#ifndef ORBITACTOR_H
#define ORBITACTOR_H

#include <Engine/include/Actor.h>

class OrbitActor : public Actor
{
public:
    explicit OrbitActor(class Game* game);

    void ActorInput(const InputState& state) override;

    void SetVisible(bool visible) const;

private:
    class OrbitCamera* mCam;
    class MeshComponent* mMeshComp;
    Vector3 mCamOffset{-400.0f, 0.0f, 0.0f};
};

#endif //ORBITACTOR_H
